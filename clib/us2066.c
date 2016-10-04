#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <wiringPi.h>

#include "us2066SPI.c"
#include "us2066.h"

const int rowSelectCommands[] = {0x80, 0xA0, 0xC0, 0xE0};
const unsigned char charPositions[4][20] = {
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13},
    {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33},
    {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53},
    {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73}
};
const unsigned char screenRows = 4;
const unsigned char screenCols = 20;


void doubleLineText(int mode)
{
    if (mode == NHD_TWOLINE_MODE_OFF) {
        command(0b00101000);  //______ function set (extended command set) - Disable 2-line characters
    }
    else if (mode == NHD_TWOLINE_MODE_112) {
        command(0b00101110);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 1
        command(0b00010001);  //__RE__ Double Height (4-line), both lines double height
        command(0b00101100);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 0
    }
    else if (mode == NHD_TWOLINE_MODE_121) {
        command(0b00101110);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 1
        command(0b00010101);  //__RE__ Double Height (4-line), both lines double height
        command(0b00101100);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 0
    }
    else if (mode == NHD_TWOLINE_MODE_22) {
        command(0b00101110);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 1
        command(0b00011001);  //__RE__ Double Height (4-line), both lines double height
        command(0b00101100);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 0
    }
    else if (mode == NHD_TWOLINE_MODE_211) {
        command(0b00101110);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 1
        command(0b00011101);  //__RE__ Double Height (4-line), both lines double height
        command(0b00101100);  //______ function set (extended command set) - Enable 2-line characters  -> RE = 0
    }
    else {
        printf("\noled_doubleLineText(%d):> Unknown 2LINE_MODE\n", mode);
        exit(-1);
    }
}

void displayOnOff(bool on, bool cursor, bool blink) {
    unsigned short byte = 0b00001000;

    if (on) {
        byte |= 4; //Put the 4th bit on
    }
    if (cursor) {
        byte |= 2;
    }
    if (blink) {
        byte |= 1;
    }

    command(byte);
}

void printRow(int rowIndex, char row[]) {
    moveCursorToPos(rowIndex, 0);

    int i;
    for(i=0;i<screenCols;i++){
        data(row[i]);
    }
}

char *readRow(int rowIndex, char *bytes) {
    moveCursorToPos(rowIndex, 0);
    int i;
    readData(); //Read columns+1 count of bytes. The first byte is always a bogus-byte needed by the MPU to prepare for the incoming read operations
    for(i=0;i<screenCols;i++){
        bytes[i] = readData();
    }
    return bytes;
}

void moveCursorToPos(int rowIndex, int colIndex) {
    unsigned char byte = charPositions[rowIndex][colIndex];
    byte |= 128; //Put the 8th bit on to tell the MPU that this is a "Set DDRAM Address"-command
    command(byte);
}

void clearDisplay() {
    command(0b00000001);
}

/*
  ------------Initialization functions-------------
*/

void init() {
    wiringPiSetup();

    pinMode(spi_pin_cs, OUTPUT);
    pinMode(spi_pin_res, OUTPUT);
    pinMode(spi_pin_sclk, OUTPUT);
    pinMode(spi_pin_sdin, OUTPUT);
    pinMode(spi_pin_sdout, INPUT);

    digitalWrite(spi_pin_sclk, HIGH);
    digitalWrite(spi_pin_sdin, HIGH);

    //Soft-reset the display for a new try of configurations to take effect.
    digitalWrite(spi_pin_res, LOW);
    usleep(500);
    digitalWrite(spi_pin_res, HIGH);
    usleep(500);

    command(0b00101010);  //______ function set (extended command set)       -> RE == 1, IS == 0
    command(0b01110001);  //__RE__ function selection A, disable internal Vdd regualtor
    data(   0b00000000);
    command(0b00101000);  //__RE__ function set (fundamental command set)    -> RE == 0, IS == 0
    command(0b00001000);  //______ display off, cursor off, blink off
    command(0b00101010);  //______ function set (extended command set)       -> RE == 1, IS == 0
    command(0b01111001);  //__RE__ OLED command set enabled                  -> SD == 1
    command(0b11010101);  //__RESD set display clock divide ratio/oscillator frequency
    command(0b01110000);  //__RESD set display clock divide ratio/oscillator frequency  - This doesn't do anything if this is driven via an external SCLK
    command(0b01111000);  //__RESD OLED command set disabled                 -> SD == 0
    command(0b00001001);  //__RE__ extended function set (4-lines)
    command(0b00000110);  //__RE__ COM SEG direction                                    - Pretty deep stuff, controls in which direction the device registers are loaded
    command(0b01110010);  //__RE__ function selection B, Select the character no. of character generator
    data(   0b00000000);  //__RE__ ROM CGRAM selection
    //command(0b00101010);  //__RE__ function set (extended command set)                - This is not needed because RE is already selected
    command(0b01111001);  //__RE__ OLED command set enabled                  -> SD == 1
    command(0b11011010);  //__RESD set SEG pins hardware configuration
    command(0b00010000);  //__RESD set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
    command(0b11011100);  //__RESD function selection C
    command(0b00000000);  //__RESD function selection C
    command(0b10000001);  //__RESD set contrast control
    command(0b11111111);  //__RESD set contrast control
    command(0b11011001);  //__RESD set phase length
    command(0b11110001);  //__RESD set phase length                                     - This is a pretty good value :) Change this to 0b00000000 for nice effects
    command(0b11011011);  //__RESD set VCOMH deselect level
    command(0b01000000);  //__RESD set VCOMH deselect level                             - This is beyond me
    command(0b01111000);  //__RESD OLED command set disabled                 -> SD == 0
    command(0b00101000);  //__RE__ function set (fundamental command set)    -> RE == 0, IS == 0
    command(0b00000001);  //______ clear display
    command(0b10000000);  //______ set DDRAM address to 0x00
    command(0b00001100);  //______ display ON

    usleep(250000);
}

/*
  Set global parameters
*/
void setSpiTiming(int SpiTiming) {
    spi_timing = SpiTiming;
}
void setSpiReceiveDelay(int SpiReceiveDelay) {
    spi_receiveDelay = SpiReceiveDelay;
}
void setSpiSendDelay(int SpiSendDelay) {
    spi_sendDelay = SpiSendDelay;
}
void setSpiPinRES(unsigned char pin) {
    spi_pin_res = pin;
    pinMode(spi_pin_res, OUTPUT);
}
void setSpiPinCS(unsigned char pin) {
    spi_pin_cs = pin;
    pinMode(spi_pin_cs, OUTPUT);
}
void setSpiPinSCLK(unsigned char pin) {
    spi_pin_sclk = pin;
    pinMode(spi_pin_sclk, OUTPUT);
    digitalWrite(spi_pin_sclk, HIGH);
}
void setSpiPinSDIN(unsigned char pin) {
    spi_pin_sdin = pin;
    pinMode(spi_pin_sdin, OUTPUT);
    digitalWrite(spi_pin_sdin, HIGH);
}
void setSpiPinSDOUT(unsigned char pin) {
    spi_pin_sdout = pin;
    pinMode(spi_pin_sdout, INPUT);
}

/*
#include <time.h>
char *get_time(char *timess)
{
  time_t ltime;
  time(&ltime);
  char bytes[] = {1,2,3,4};
  //return ctime(&ltime);
  return timess;
}
*/
