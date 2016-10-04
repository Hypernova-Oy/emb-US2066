#!/usr/bin/bash

op=$1

app_dir=`pwd`
cd $app_dir
buildDir="./cbuild"
clib="./clib"
lib="./lib"
csharedDir="/usr/lib"

function compile {
  gccWiringPiDeps="-lwiringPi -llib"

  gcc -Wall -o us2066 $clib"/us2066.c" $gccWiringPiDeps
}

function install_kernel {
  gpio load spi
}

function link {
  echo cp $lib/RTTTL/XS.so $csharedDir/XS.so
}

function unlink {
  echo rm $csharedDir/XS.so
}


function install {
    install_kernel
    compile
    link
}

function remove {
    gpio unload spi
}

if [ "$op" == "install" ]
then
  install
elif [ "$op" == "uninstall" ]
then
  link
elif [ "$op" == "link" ]
then
  link
elif [ "$op" == "unlink" ]
then
  unlink
else
  echo "Unknown \$op $op"
  exit 0
fi
