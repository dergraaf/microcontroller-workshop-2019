#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019, Fabian Greif
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

import os
import string
import re
import math

template_source = """
#include <stdint.h>

namespace bitmap
{
constexpr uint8_t ${name}[${array_length}] =
{
    ${width}, ${height},
    ${array}
};
}

"""

template_header = """
#ifndef ${include_guard}
#define ${include_guard}

#include <stdint.h>

namespace bitmap
{
/**
 * \\brief    Generated bitmap
 *
 * Generated from file "${filename}".
 *
 * - Width  : ${width}
 * - Height : ${height}
 *
 * \\ingroup    image
 */
extern constexpr uint8_t ${name}[${array_length}] =
{
    ${width}, ${height},
    ${array}
};
}

#endif

"""

if __name__ == '__main__':
    filename_in = os.sys.argv[1]
    filename_out = os.sys.argv[2]

    input = open(filename_in).read()
    if input[0:3] != "P1\n":
        env.Error("Error: format needs to be a portable bitmap in "
                  "ASCII format (file descriptor 'P1')!")
        exit(1)

    input = input[3:]
    while input[0] == "#" or input[0] in string.whitespace:
        # switch to the next line
        input = input[input.find("\n") + 1:]

    result = re.match("^(\d+) (\d+)\n", input)
    if not result:
        env.Error("Error: bad format!")

    width = int(result.group(1))
    height = int(result.group(2))

    rows = int(math.ceil(height / 8.0))

    # now we finally have the raw data
    input = input[result.end():]
    input = input.replace("\n", "")

    data = []
    for y in range(rows):
        data.append([0 for row in range(width)])

    for y in range(height):
        for x in range(width):
            index = x + y * width
            if input[index] == "1":
                data[y // 8][x] |= 1 << (y % 8)

    array = []
    for y in range(rows):
        line = []
        for x in range(width):
            line.append("0x%02x," % data[y][x])
        array.append(" ".join(line))

    basename = os.path.splitext(os.path.basename(filename_out))[0]
    substitutions = {
        'name': basename,
        'filename': filename_in,
        'width': width,
        'height': height,
        'array': "\n    ".join(array),
        'array_length': int(width * rows + 2),
        'include_guard': "IMAGES_" + basename.upper().replace(" ", "_") + "_HPP"
    }

    # output = string.Template(template_source).safe_substitute(substitutions)
    # open(os.path.splitext(filename_out)[0] + ".cpp", 'w').write(output)

    output = string.Template(template_header).safe_substitute(substitutions)
    open(os.path.splitext(filename_out)[0] + ".hpp", 'w').write(output)
