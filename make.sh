#!/usr/bin/bash

op=$1

app_dir=`pwd`
cd $app_dir
buildDir="./cbuild"
clib="./clib"
lib="./lib"
csharedDir="/usr/lib"

bash make-swig.sh

perl ./Build.PL
perl ./Build installdeps
perl ./Build install
perl ./Build realclean
