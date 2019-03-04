# Copyright (c) 2019, Fabian Greif
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

all: build

prepare:
	lbuild -c project.xml -p . build

build:
	scons -j4 bin

program: build
	dfu-util -d 1eaf:0003 -a 2 -D build/release/display.bin -R

PBM_TOOL = ../../tools/bitmap.py
IMAGES_IN  = $(wildcard images/*.pbm)
IMAGES_OUT = $(IMAGES_IN:images/%.pbm=images/%.hpp)

convert: $(IMAGES_OUT)
images/%.hpp: images/%.pbm
	python3 $(PBM_TOOL) "$<" "$@"

clean:
	$(RM) -r build/*

clean-images:
	$(RM) $(IMAGES_OUT)

.PHONY : prepare build program
