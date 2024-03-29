#!/usr/bin/perl

use Modern::Perl;

use Test::More tests => 3;


use OLED::us2066;

print "##These are manual tests to verify the Perl-interface talks correctly with the C-library##\n";
print "##Check your SPI cabling and keep an eye on the OLED display for the fireworks to begin!##\n";
print "\n";
print "##The OLED display also communicates with Raspberry Pi and this test is useful when ran automatically##\n";

subtest "Set SPI pins prior to initialization", sub {
    OLED::us2066::setSpiPinSCLK(  11  );
    OLED::us2066::setSpiPinSDIN(  10  );
    OLED::us2066::setSpiPinSDOUT(  9  );
    OLED::us2066::setSpiPinCS(     8  );
    OLED::us2066::setSpiPinRES(   25  );
    OLED::us2066::setSpiSendDelay(10  );
    OLED::us2066::setSpiReceiveDelay(50);
    OLED::us2066::init();
    OLED::us2066::displayOnOff(1,0,0);
    ok(1, "Didn't crash");
};

subtest "Multiple init-calls don't cause crashing", sub {
    OLED::us2066::init();
    OLED::us2066::init();
    ok(1, "Didn't crash");
};

subtest "Test that hardware is properly configured", sub {
    my (@msg, $readBytes);
    $msg[0] = "KUHA ON TARKASTANUT ";
    $msg[1] = "POYTAKIRJAN. KUHA ON";
    $msg[2] = "PAIKALLA VALTUUSTOSS";
    $msg[3] = "A. KUHA ON ASEMAKAAV";

    OLED::us2066::init();

    OLED::us2066::displayOnOff(1,0,0);

    for(my $i=0 ; $i<4 ; $i++) {
        $readBytes = "                    "; #Pointer to this string is passed to C and replaced with the read data from the MPU.
        OLED::us2066::printRow($i, $msg[$i]);
        OLED::us2066::readRow($i, $readBytes);
        is($readBytes, $msg[$i], "Wrote to the display DDRAM and confirmed that the DDRAM has the values we wrote - $i");
    }
    sleep 1;
    OLED::us2066::displayOnOff(0,0,0);
};

done_testing;
