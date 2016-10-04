#!/usr/bin/perl

use Modern::Perl;

use Test::More;


use OLED::us2066;

subtest "Test that hardware is properly configured", \&hardwareCheck;
sub hardwareCheck {
    my (@msg, $readBytes);
    $msg[0] = "KUHA ON TARKASTANUT ";
    $msg[1] = "POYTAKIRJAN. KUHA ON";
    $msg[2] = "PAIKALLA VALTUUSTOSS";
    $msg[3] = "A. KUHA ON ASEMAKAAV";

    OLED::us2066::init();

    while (1) {
        OLED::us2066::displayOnOff(1,0,0);

        for(my $i=0 ; $i<4 ; $i++) {
            $readBytes = "                    "; #Pointer to this string is passed to C and replaced with the read data from the MPU.
            OLED::us2066::printRow($i, $msg[$i]);
            OLED::us2066::readRow($i, $readBytes);
            is($readBytes, $msg[$i], "Wrote to the display DDRAM and confirmed that the DDRAM has the values we wrote - $i");
        }


        OLED::us2066::displayOnOff(0,0,0);
        sleep 1;
    }
}
