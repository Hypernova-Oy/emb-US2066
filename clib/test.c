#include <stdio.h>
#include <stdlib.h>

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

int main(int argc,char const *argv[])
{
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
        run2();

    }
}
