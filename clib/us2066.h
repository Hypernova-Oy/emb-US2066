#ifndef US2066_HEADER_FILE
#define US2066_HEADER_FILE

#define NHD_TWOLINE_MODE_OFF 0
#define NHD_TWOLINE_MODE_112 1
#define NHD_TWOLINE_MODE_121 2
#define NHD_TWOLINE_MODE_22  3
#define NHD_TWOLINE_MODE_211 4

void doubleLineText(int mode);
void displayOnOff(bool on, bool cursor, bool blink);
void printRow(int rowIndex, char row[]);
char *readRow(int rowIndex, char *bytes);
void moveCursorToPos(int rowIndex, int colIndex);
void clearDisplay();

void setSpiTiming(int SpiTiming);
void setSpiReceiveDelay(int SpiReceiveDelay);
void setSpiSendDelay(int SpiSendDelay);
void setSpiPinRES(unsigned char pin);
void setSpiPinCS(unsigned char pin);
void setSpiPinSCLK(unsigned char pin);
void setSpiPinSDIN(unsigned char pin);
void setSpiPinSDOUT(unsigned char pin);
void init();

//extern char *get_time(char *timess);
#endif /* US2066_HEADER_FILE */
