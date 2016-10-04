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


