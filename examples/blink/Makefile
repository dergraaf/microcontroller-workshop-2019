

build:
	scons -j4 bin

program:
	dfu-util -d 1eaf:0003 -a 2 -D build/release/blink.bin -R

prepare:
	lbuild -c project.xml -p . build

.PHONY : prepare build program
