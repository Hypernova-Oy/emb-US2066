echo "Compiling the logger as a standalone"
gcc logger.c -o logger
echo "Test it with:"
echo "./logger"
echo ""
echo "Compiling the us2066 as a standalone"
gcc -D NOMAIN -c logger.c
gcc us2066SPI.c us2066.c test.c -lwiringPiDev -lwiringPi -lcrypt
#gcc logger.o us2066SPI.o us2066.o test.o -o test -lwiringPiDev -lwiringPi -lcrypt
echo "Test it with:"
echo "./test"
echo ""
