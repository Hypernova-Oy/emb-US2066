#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <wiringPi.h>

#include "us2066SPI.h"

/*
  These package variables are overwritten from the us2066.c::init()-function
*/
int spi_timing = 250;
int spi_receiveDelay = 50; //When we receive bits from the MPU, we need to give time for the MPU's registers to populate after receiving the "read"-command
int spi_sendDelay = 0; //When we send bits, the MPU might need to process the bits before receiving new ones.
//Using wiringPi pin notation
unsigned char spi_pin_res = 30;
unsigned char spi_pin_cs = 10;
unsigned char spi_pin_sclk = 14;
unsigned char spi_pin_sdin = 12;
unsigned char spi_pin_sdout = 13;

//#define spi_pin_res    30
//#define spi_pin_cs     10
#define SCLK   14
#define SDIN   12
#define SDOUT  13
/*
  EO package variable definition
*/



void chipSelect(bool on) {
    digitalWrite(spi_pin_cs, (!on)); //LOW is actually the chip selected value, so if we want to activate the chip, we invert the boolean
}
void _sendBit(int bit) {
    digitalWrite(SCLK, LOW);
    //usleep(spi_sendDelay);
    digitalWrite(SDIN, bit);
    //usleep(spi_sendDelay);
    digitalWrite(SCLK, HIGH);
    //usleep(spi_sendDelay);
}
bool _receiveBit() {
    digitalWrite(SCLK, LOW);
    usleep(spi_receiveDelay);
    bool bit = digitalRead(SDOUT);
    usleep(spi_receiveDelay);
    digitalWrite(SCLK, HIGH);
    usleep(spi_receiveDelay);
    //printf("_receiveBit: %d\n", bit);
    return bit;
}
unsigned char _receiveByte() {
    digitalWrite(SDIN, LOW); //Don't send anything, keep this LOW during receival

    unsigned char byte = 0x00;
    short i;
    for(i=0;i<8;i++){
        if (_receiveBit()) {
            byte |= 1 << i; //Receive bits from MCU, least significant bit first
        }
    }
    return byte;
}
void _startByte(bool dc, bool rw) {
    //printf("Start byte transfer\n");
    //Five concurrent HIGHs
    _sendBit(1);
    _sendBit(1);
    _sendBit(1);
    _sendBit(1);
    _sendBit(1);

    //R/W selection
    _sendBit(rw);

    //data or command selection
    _sendBit(dc);

    //Start byte end bit
    _sendBit(0);
}
void _write(unsigned char byte) {
    //printf("Start write payload transfer\n");
    //Send first 4 payload bits, lower data
    _sendBit((byte&1));
    _sendBit((byte&2));
    _sendBit((byte&4));
    _sendBit((byte&8));

    //Send first 4 safety empty bits
    _sendBit(0);
    _sendBit(0);
    _sendBit(0);
    _sendBit(0);

    //Send second 4 payload bits, upper data
    _sendBit((byte&16));
    _sendBit((byte&32));
    _sendBit((byte&64));
    _sendBit((byte&128));

    //Send second 4 safety empty bits
    _sendBit(0);
    _sendBit(0);
    _sendBit(0);
    _sendBit(0);
}
void command(unsigned char byte) {
    chipSelect(1);
    _startByte(0, 0);
    _write(byte);
    usleep(spi_timing); //Break to give time for NHD to process the instruction
    chipSelect(0);
}
unsigned char readCommand() {
    //TODO:: This may not work.

    chipSelect(1);
    _startByte(0, 1);
    usleep(1000);

    unsigned char byte = _receiveByte();

    chipSelect(0);
    return byte;
}
void data(unsigned char byte) {
    chipSelect(1);
    _startByte(1, 0);
    _write(byte);
    usleep(spi_timing); //Break to give time for NHD to process the instruction
    chipSelect(0);
}
unsigned char readData() {
    //TODO:: This may not work.

    chipSelect(1);
    _startByte(1, 1);
    usleep(1000);

    unsigned char byte = _receiveByte();

    chipSelect(0);
    return byte;
}