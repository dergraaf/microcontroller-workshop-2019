/*
 * Copyright (c) 2019, Fabian Greif
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_BUFFERED_GRAPHIC_DISPLAY_HORIZONTAL_HPP
#define MODM_BUFFERED_GRAPHIC_DISPLAY_HORIZONTAL_HPP

#include <stdlib.h>

#include <modm/ui/display/graphic_display.hpp>

namespace modm
{
/**
 * Base class for graphical displays with a RAM buffer.
 *
 * Every operation works on the internal RAM buffer, therefore the content
 * of the real display is not changed until a call of update().
 *
 * \tparam	Width	Width of the display. Must be a multiple of 8!
 * \tparam	Height	Height of the display.
 *
 * \author	Fabian Greif
 * \ingroup	modm_ui_display
 */
template <uint16_t Width, uint16_t Height>
class BufferedGraphicDisplayHorizontal : public GraphicDisplay
{
    // Height must be a multiple of 8
    static_assert((Width % 8) == 0, "width must be a multiple of 8");

public:
    static constexpr uint16_t displayBufferWidth = Width / 8;
    static constexpr uint16_t displayBufferHeight = Height;

    virtual
    ~BufferedGraphicDisplayHorizontal() = default;

    virtual inline uint16_t
    getWidth() const override
    {
        return Width;
    }

    virtual inline uint16_t
    getHeight() const override
    {
        return Height;
    }

    virtual void
    clear() override;

protected:
    virtual void
    setPixel(int16_t x, int16_t y) override;

    virtual void
    clearPixel(int16_t x, int16_t y) override;

    virtual bool
    getPixel(int16_t x, int16_t y) override;

    uint8_t mDisplayBuffer[displayBufferHeight][displayBufferWidth];
};
}

#include "buffered_graphic_display_horizontal_impl.hpp"

#endif
