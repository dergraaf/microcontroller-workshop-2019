
#ifndef IMAGES_SPACE_INVADER_HPP
#define IMAGES_SPACE_INVADER_HPP

#include <stdint.h>
#include <modm/architecture/interface/accessor.hpp>

namespace bitmap
{
/**
 * \brief    Generated bitmap
 *
 * Generated from file "images/space_invader.pbm".
 *
 * - Width  : 11
 * - Height : 8
 *
 * \ingroup    image
 */
extern constexpr uint8_t space_invader[13] =
{
    11, 8,
    0x70, 0x18, 0x7d, 0xb6, 0xbc, 0x3c, 0xbc, 0xb6, 0x7d, 0x18, 0x70,
};

static auto space_invader_accessor = modm::accessor::Flash<uint8_t>(space_invader);
}

#endif

