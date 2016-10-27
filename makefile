cBuildDir=./cbuild
cLib=./clib
pLib=./lib
pPackage=OLED
systemCDir=/usr/lib
systemConfigBaseDir=/etc
programName=emb-rtttl

cLibName=us2066
gccWiringPiDeps=-lwiringPi


debianPackages=perl swig
debianPackagedPerlModules=libtest-simple-perl

#Macro to check the exit code of a make expression and possibly not fail on warnings
RC      := test $$? -lt 100 


build: compile

restart:

install: installPackages build perlDeploy link configure

installPackages:
	sudo apt-get install -y $(debianPackages)
	sudo apt-get install -y $(debianPackagedPerlModules)

perlDeploy:
	./Build installdeps
	./Build install

compile:
	##BUILD Perl XS madness using handy dandy swig <3
	mkdir -p $(cBuildDir)
	cp -r $(cLib)/* $(cBuildDir)/
	cd $(cBuildDir); \
	\
	swig -perl5 $(cLibName).i; \
	\
	gcc -c `perl -MConfig -e 'print join(" ", @Config{qw(ccflags optimize cccdlflags)}, \
	       	"-I$$Config{archlib}/CORE")'` $(cLibName).c $(cLibName)_wrap.c $(gccWiringPiDeps); \
	\
	gcc -shared `perl -MConfig -e 'print $$Config{lddlflags}'` $(cLibName).o $(cLibName)_wrap.o -o $(cLibName).so $(gccWiringPiDeps); \
	gcc -Wall -o test test.c $(gccWiringPiDeps);

	mkdir -p $(pLib)/$(pPackage)
	cp $(cBuildDir)/$(cLibName).pm $(pLib)/$(pPackage)/
	cp $(cBuildDir)/$(cLibName).so $(pLib)/$(pPackage)/
	cp $(cBuildDir)/test $(cLib)/test

	rm -r $(cBuildDir)

	#Build Perl modules
	perl Build.PL
	./Build

test:
	#$(cLib)/test #c-tests are on an endless loop.
	prove -Ilib -I. t/*.t

configure:

unconfigure:

link: compile
	cp $(pLib)/$(pPackage)/$(cLibName).so $(systemCDir)/$(cLibName).so

unlink:
	rm $(systemCDir)/$(cLibName).so || $(RC)

clean:
	rm $(pLib)/$(pPackage)/$(cLibName).so || $(RC)
	./Build realclean

uninstall: unlink unconfigure clean

