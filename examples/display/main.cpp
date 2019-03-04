/*
 * Copyright (c) 2019, Fabian Greif
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <atomic>
#include <array>
#include <stdint.h>

#include <modm/board.hpp>
#include <modm/processing.hpp>

#include <modm/ui/button_group.hpp>

#include "dot_matrix_max7219_horizontal.hpp"

#include "images/space_invader.hpp"
#include "images/space_invader_2.hpp"

using Led = GpioInverted<GpioOutputB12>;

using Cs = GpioOutputA8;

using Button0 = GpioInputB4;
using Button1 = GpioInputB3;

using Buttons = SoftwareGpioPort<Button1, Button0>;

static modm::ButtonGroup<> buttons(0x03);

static modm::DotMatrixMax7219Horizontal<SpiMaster2, Cs, 2, 1> display;

static inline void
initialize()
{
    Board::systemClock::enable();
    modm::cortex::SysTickTimer::initialize<Board::systemClock>();

    Led::setOutput(modm::Gpio::Low);
    Led::set();

    // Disable JTAG to release PB3/4
    AFIO->MAPR |= (AFIO->MAPR & AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    Button0::setInput(modm::platform::Gpio::InputType::PullUp);
    Button1::setInput(modm::platform::Gpio::InputType::PullUp);

    // Initialize buttons
    buttons.update(Buttons::read());
    buttons.update(Buttons::read());
    buttons.update(Buttons::read());
    buttons.update(Buttons::read());

    buttons.isPressed(0xFF);

    Usart1::connect<GpioOutputA9::Tx, GpioInputA10::Rx>();
    Usart1::initialize<Board::systemClock, 115200>();

    Cs::setOutput(modm::Gpio::High);

    SpiMaster2::connect<GpioOutputB13::Sck, GpioOutputB15::Mosi, GpioInputB14::Miso>();
    SpiMaster2::initialize<Board::systemClock, 100000ul, 10000>();
    SpiMaster2::setDataMode(SpiMaster2::DataMode::Mode3);

    modm::IODeviceWrapper<Usart1, modm::IOBuffer::BlockIfFull> wrapper;
    modm::IOStream stream(wrapper);

    display.initialize();
    display.setBrightness(1);
    display.clear();
    display.update();
}

int
main()
{
    initialize();

    display.setFont(modm::font::ScriptoNarrow);
    display.setCursor({0, 1});
    display << "Hello";
    display.update();

    modm::delayMilliseconds(1000);
    display.clear();
    display.setCursor({2, 1});
    display << "C++";
    display.update();

    modm::delayMilliseconds(1000);

    uint8_t x = 0;
    uint8_t y = 0;

    uint8_t intensity = 1;

    const uint8_t maxX = display.getWidth() - 1;
    const uint8_t maxY = display.getHeight() - 1;

    modm::ShortPeriodicTimer timerDisplay(100);
    modm::ShortPeriodicTimer timerButton(10);
    while (true)
    {
        if (timerDisplay.execute())
        {
            if (intensity > 0)
            {
                display.clear();
                display.drawLine(modm::glcd::Point(x, y),
                                 modm::glcd::Point(maxX - x, maxY - y));
                display.update();

                if (x == 0)
                {
                    if (++y == maxY)
                    {
                        ++x;
                    }
                }
                else if (x == maxX)
                {
                    if (--y == 0)
                    {
                        --x;
                    }
                }
                else if (y == 0)
                {
                    if (--x == 0)
                    {
                        ++y;
                    }
                }
                else if (y == maxY)
                {
                    if (++x == maxX)
                    {
                        --y;
                    }
                }
            }
            else
            {
                static uint8_t counter = 0;

                ++counter;
                if (counter == 5)
                {
                    display.clear();
                    display.drawImage({2, 0}, bitmap::space_invader_accessor);
                    display.update();
                }
                else if (counter == 10)
                {
                    counter = 0;
                    display.clear();
                    display.drawImage({2, 0}, bitmap::space_invader_2_accessor);
                    display.update();
                }
            }
        }

        if (timerButton.execute())
        {
            buttons.update(Buttons::read());

            Led::reset();
            if (buttons.isPressed(buttons.BUTTON0))
            {
                if (intensity < 15)
                {
                    Led::set();
                    display.setBrightness(++intensity);
                }
            }

            if (buttons.isPressed(buttons.BUTTON1))
            {
                if (intensity > 0)
                {
                    Led::set();
                    display.setBrightness(--intensity);
                }
            }

            //Led::set(Button1::read());
        }
    }

    return 0;
}
