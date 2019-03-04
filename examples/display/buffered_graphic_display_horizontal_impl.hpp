/*
 * Copyright (c) 2019, Fabian Greif
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "buffered_graphic_display_horizontal.hpp"

namespace modm
{
template <uint16_t Width, uint16_t Height>
void
BufferedGraphicDisplayHorizontal<Width, Height>::clear()
{
    for (uint_fast16_t y = 0; y < displayBufferHeight; ++y) {
        for (uint_fast16_t x = 0; x < displayBufferWidth; ++x) {
            mDisplayBuffer[y][x] = 0;
        }
    }

    // reset the cursor
    this->cursor = glcd::Point(0, 0);
}

template <uint16_t Width, uint16_t Height>
void
BufferedGraphicDisplayHorizontal<Width, Height>::setPixel(int16_t x, int16_t y)
{
    if (static_cast<uint16_t>(x) < Width && static_cast<uint16_t>(y) < Height) {
        mDisplayBuffer[y][x / 8] |= (1 << (x & 0x07));
    }
}

template <uint16_t Width, uint16_t Height>
void
BufferedGraphicDisplayHorizontal<Width, Height>::clearPixel(int16_t x, int16_t y)
{
    if (static_cast<uint16_t>(x) < Width && static_cast<uint16_t>(y) < Height) {
        mDisplayBuffer[y][x / 8] &= ~(1 << (x & 0x07));
    }
}

template <uint16_t Width, uint16_t Height>
bool
BufferedGraphicDisplayHorizontal<Width, Height>::getPixel(int16_t x, int16_t y)
{
    if (static_cast<uint16_t>(x) < Width && static_cast<uint16_t>(y) < Height) {
        return (mDisplayBuffer[y][x / 8] & (1 << (x & 0x07)));
    }
    else {
        return false;
    }
}
}
