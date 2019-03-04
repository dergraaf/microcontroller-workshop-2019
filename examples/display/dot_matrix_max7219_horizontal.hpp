/*
 * Copyright (c) 2014, Niklas Hauser
 * Copyright (c) 2014, Sascha Schade
 * Copyright (c) 2019, Fabian Greif
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef MODM_DOT_MATRIX_MAX7219_HORIZONTAL_HPP
#define MODM_DOT_MATRIX_MAX7219_HORIZONTAL_HPP

#include <modm/driver/display/max7219matrix.hpp>

#include "buffered_graphic_display_horizontal.hpp"

namespace modm
{
template<typename SPI, typename CS, uint8_t COLUMNS = 1, uint8_t ROWS = 1>
class DotMatrixMax7219Horizontal : public BufferedGraphicDisplayHorizontal<8 * COLUMNS, 8 * ROWS>
{
public:
    virtual
    ~DotMatrixMax7219Horizontal() = default;

    inline void
    initialize()
    {
        mDriver.initialize();
        mDriver.clear();
    }

    /**
     * Set the brightness of the whole matrix.
     *
     * \param intensity range 0 to 15.
     */
    inline void
    setBrightness(uint8_t intensity)
    {
        mDriver.setBrightness(intensity);
    }

    virtual void
    update() override;

protected:
    Max7219<SPI, CS, COLUMNS * ROWS> mDriver;
};

// Implementation of the member functions

template<typename SPI, typename CS, uint8_t COLUMNS, uint8_t ROWS>
void
DotMatrixMax7219Horizontal<SPI, CS, COLUMNS, ROWS>::update()
{
    // Iterate column 0 to 7 of MAX LED driver
    for (uint8_t ledCol = 0; ledCol < 8; ++ledCol)
    {
        uint8_t buf[COLUMNS * ROWS];
        uint8_t idx = COLUMNS * ROWS;

        // row is the row of LED modules and
        // a group of eight pixels vertical
        for (uint8_t row = 0; row < ROWS; ++row)
        {
            // col is the column of LED modules and
            // a group of eight pixels horizontal
            for (uint8_t col = 0; col < COLUMNS; ++col)
            {
                buf[--idx] = this->mDisplayBuffer[row * 8 + ledCol][col];
            }
        }

        mDriver.setRow(7 - ledCol, buf);
    }
}
}

#endif
