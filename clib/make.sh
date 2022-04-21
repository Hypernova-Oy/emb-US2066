echo "Compiling the logger as a standalone"
gcc logger.c -o logger
echo "Test it with:"
echo "./logger"
echo ""
echo "Compiling the us2066 as a standalone"
gcc -D NOMAIN -c logger.c
gcc -I. test.c -lwiringPiDev -lwiringPi -lcrypt
echo "Test it with:"
echo "./test"
echo ""
