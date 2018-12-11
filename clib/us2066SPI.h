#ifndef US2066SPI_HEADER_FILE
#define US2066SPI_HEADER_FILE

void chipSelect(bool on);
void _sendBit(int bit);
bool _receiveBit();
unsigned char _receiveByte();
void _startByte(bool dc, bool rw);
void _write(unsigned char byte);
void command(unsigned char byte);
unsigned char readCommand();
void data(unsigned char byte);
unsigned char readData();


/*
  These package variables are overwritten from the us2066.c::init()-function
*/

int spi_timing = 250;
int spi_receiveDelay = 50; //When we receive bits from the MPU, we need to give time for the MPU's registers to populate after receiving the "read"-command
int spi_sendDelay = 0; //When we send bits, the MPU might need to process the bits before receiving new ones.

/*
  Using wiringPiSetup() pin notation, which is the wiringPi pin numbering
  This should be a list of pins physically next to each others, so they can be connected to easily
  using a single 5-pin wide female connector.
  This is important, since it makes wiring and making cables much easier.
  This implementation uses bit-banging SPI so you don't need to care about the hardware assigned SPI pins.
  Any GPIO pins do.
  see. https://pinout.xyz/

*/

unsigned char spi_pin_sclk  = 11;
unsigned char spi_pin_sdin  = 10;
unsigned char spi_pin_sdout = 9;
unsigned char spi_pin_cs    = 8;
unsigned char spi_pin_res   = 0;

/*
  EO package variable definition
*/

#endif /* US2066SPI_HEADER_FILE */
