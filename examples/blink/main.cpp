/*
 * Copyright (c) 2019, Fabian Greif
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <modm/board.hpp>
#include <modm/processing.hpp>

using Led = GpioInverted<GpioOutputB12>;

static inline void
initialize()
{
    Board::systemClock::enable();
    modm::cortex::SysTickTimer::initialize<Board::systemClock>();

    Led::setOutput(modm::Gpio::Low);
    Led::set();
}

int
main()
{
    initialize();

    while (true)
    {
        Led::set();
        modm::delayMilliseconds(100);
        Led::reset();
		modm::delayMilliseconds(900);
    }

    return 0;
}
