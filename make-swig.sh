#!/bin/bash

os_clib="/usr/lib"
clib="clib"
lib="lib"

cd $clib

##Compile Perl interface using SWIG
swig -perl5 us2066.i

gcc -c `perl -MConfig -e 'print join(" ", @Config{qw(ccflags optimize cccdlflags)}, "-I$Config{archlib}/CORE")'` us2066.c us2066_wrap.c -lwiringPi

gcc `perl -MConfig -e 'print $Config{lddlflags}'` us2066.o us2066_wrap.o -o us2066.so -lwiringPi

##Compile C test script
gcc -Wall -o test test.c -lwiringPi

##Link files to filesystem
mv us2066.so $os_clib/
mkdir -p ../$lib/OLED
mv us2066.pm ../$lib/OLED/
rm us2066.o us2066_wrap.c us2066_wrap.o

cd ..