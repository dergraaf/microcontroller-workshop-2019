
#ifndef IMAGES_SPACE_INVADER_2_HPP
#define IMAGES_SPACE_INVADER_2_HPP

#include <stdint.h>
#include <modm/architecture/interface/accessor.hpp>

namespace bitmap
{
/**
 * \brief    Generated bitmap
 *
 * Generated from file "images/space_invader_2.pbm".
 *
 * - Width  : 11
 * - Height : 8
 *
 * \ingroup    image
 */
extern constexpr uint8_t space_invader_2[13] =
{
    11, 8,
    0x1e, 0x38, 0xbd, 0x76, 0x3c, 0x3c, 0x3c, 0x76, 0xbd, 0x38, 0x1e,
};

static auto space_invader_2_accessor = modm::accessor::Flash<uint8_t>(space_invader_2);
}

#endif

