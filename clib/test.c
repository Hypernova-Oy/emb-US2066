#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "us2066.c"

char text1[] = {"   Please Support   "};
char text2[] = {"    Open-Source     "};
char text3[] = {"Hardware & Software!"};
char text4[] = {"--------------------"};

char text5[] = {"  Newhaven Display  "};
char text6[] = {"4x20  Character OLED"};
char text7[] = {"    Slim  Design    "};

void blocks()
{
	int i;
    for(i=0;i<80;i++){
        data(0x1F);
        usleep(10000);
    }
}

void printRows() {
    int dur = 250;
    printRow(0, text1);
    delay(dur);
    printRow(1, text2);
    delay(dur);
    printRow(2, text3);
    delay(dur);
    printRow(3, text4);
    delay(dur);
    printRow(0, text5);
    delay(dur);
    printRow(0, text6);
    delay(dur);
    printRow(0, text7);
    delay(dur);
}



//assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void run1() {
    displayOnOff(1,1,0);

    blocks();
    printRows();

    doubleLineText(NHD_TWOLINE_MODE_112);

    blocks();
    printRows();

    doubleLineText(NHD_TWOLINE_MODE_22);

    blocks();
    printRows();

    doubleLineText(NHD_TWOLINE_MODE_211);

    blocks();
    printRows();

    doubleLineText(NHD_TWOLINE_MODE_OFF);

    blocks();
    printRows();
    blocks();

    clearDisplay();
    displayOnOff(0,0,0);
}

void run2() {
    unsigned char byte;
    short i;

    displayOnOff(1,0,0);

    delay(500);
    printRow(0, text3);
    delay(500);
    char bytes[20];
    readRow(0, bytes);
    printf("\nreadRow()\n%s\n", bytes);

    printf("Strcomp\n");
    for (i=0;i<20;i++) {
        if (bytes[i] == text3[i]) {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    printf("\n");

    delay(500);
    moveCursorToPos(0,0);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);
    byte = readData();
    printBits(sizeof(byte), &byte);
    printf("Char: %c\n", byte);

    moveCursorToPos(0,0);
    data(0x1F);
    data(0x1F);
    data(0x1F);
    data(0x1F);
    data(0x1F);
    data(0x1F);
    data(0x1F);
    data(0x1F);
    data(0x1F);
    data(0x1F);

//    delay(500);
//    moveCursorToPos(0,2);
//    byte = readData();
//    printBits(sizeof(byte), &byte);
//    data(0x1F);

//    clearDisplay();
//    displayOnOff(0,0,0);
}

void testPins()
{
    wiringPiSetupGpio();

    pinMode(spi_pin_sclk, OUTPUT);
    pinMode(spi_pin_sdin, OUTPUT);
    pinMode(spi_pin_sdout, OUTPUT);
    pinMode(spi_pin_cs, OUTPUT);
    pinMode(spi_pin_res, OUTPUT);

    printf("\nSPI pin SCLK check");
    digitalWrite(spi_pin_sclk, HIGH);
    usleep(1000000);
    digitalWrite(spi_pin_sclk, LOW);

    printf("\nSPI pin SDIN check");
    digitalWrite(spi_pin_sdin, HIGH);
    usleep(1000000);
    digitalWrite(spi_pin_sdin, LOW);

    printf("\nSPI pin SDOUT check");
    digitalWrite(spi_pin_sdout, HIGH);
    usleep(1000000);
    digitalWrite(spi_pin_sdout, LOW);

    printf("\nSPI pin CS check");
    digitalWrite(spi_pin_cs, HIGH);
    usleep(1000000);
    digitalWrite(spi_pin_cs, LOW);

    printf("\nSPI pin RES check");
    digitalWrite(spi_pin_res, HIGH);
    usleep(1000000);
    digitalWrite(spi_pin_res, LOW);

    printf("\nTest done!\n");
}

void testOled()
{
    init(); //1 microsecond wait between instructions

    printf("Running manual tests for the NHD OLED display\n");
    printf("Please stay put, stare at the OLED display and keep your hands and feet inside the vehicle\n");
    printf("This won't hurt much\n");
    printf("\n");
    printf("You will observe the following phenomena:\n");
    printf("-text in normal print as well as in double line print\n");
    printf("-blocks filling up the display from left to right, top to bottom, 4x20 region\n");
    printf("-an occasional blinking cursor\n");
    printf("-the screen shutting down after the presentation\n");
    printf("\n");
    printf("Have fun!\n");

    while (1) {

        printf("Here we go again!\n");
        run1();

    }
}

int main(int argc,char const *argv[])
{
    /*
    unsigned char byte = 0b00000000;
    printf("\nbyte:");
    printBits(sizeof(byte), &byte);
    byte |= 1;
    printBits(sizeof(byte), &byte);
    byte |= 2;
    printBits(sizeof(byte), &byte);
    byte |= 4;
    printBits(sizeof(byte), &byte);
    byte |= 8;
    printBits(sizeof(byte), &byte);
    byte |= 16;
    printBits(sizeof(byte), &byte);
    byte |= 32;
    printBits(sizeof(byte), &byte);
    byte |= 64;
    printBits(sizeof(byte), &byte);
    byte |= 128;
    printBits(sizeof(byte), &byte);
    */

    if (argc < 2)
    {
        printf("You must pass the type of test to run as parameter!\n");
        printf("Valid tests are:\n");
        printf("  pins\n");
        printf("\n");
        printf("    Blink each SPI pin. It is intended to connect SPI pins to leds to test if");
        printf("    they are properly mapped.\n");
        printf("\n");
        printf("  oled\n");
        printf("\n");
        printf("    Runs the OLED display test suite.\n");
        printf("    Make sure proper pins are wired first.\n");
        printf("\n");
        exit(2);
    }
    if (strncmp(argv[1], "pins", 4) == 0)
    {
        testPins();
    }
    else if (strncmp(argv[1], "oled", 4) == 0)
    {
        testOled();
    }
    else
    {
        printf("Unknown parameter: %s", argv[1]);
        exit(2);
    }
    return 0;
}
