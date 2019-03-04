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

.PHONY : prepare build program
