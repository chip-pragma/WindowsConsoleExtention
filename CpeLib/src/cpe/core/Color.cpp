#include "Color.h"

namespace cpe {

Color::Color(uint8_t r, uint8_t g, uint8_t b) noexcept {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(const PlatformColor &platformColor) noexcept : Color() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    const uint8_t MIN = 128u;
    const uint8_t PLUS = 127;
    auto i = MIN;
    if ((platformColor & 8u) == 8u)
        i += PLUS;
    if ((platformColor & 4u) == 4u)
        r = i;
    if ((platformColor & 2u) == 2u)
        g = i;
    if ((platformColor & 1u) == 1u)
        b = i;
#endif
}

PlatformColor Color::toPlatform() const noexcept {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    PlatformColor pc =
            _winapi::getColorComponentBit(r, _winapi::BitCol::RED)
            | _winapi::getColorComponentBit(g, _winapi::BitCol::GREEN)
            | _winapi::getColorComponentBit(b, _winapi::BitCol::BLUE);
    return pc;
#endif
}

bool Color::operator==(const Color &rhs) const {
    return r == rhs.r &&
           g == rhs.g &&
           b == rhs.b;
}

bool Color::operator!=(const Color &rhs) const {
    return !(rhs == *this);
}


namespace Colors {

const Color BLACK(0, 0, 0);
const Color BLUE(0, 0, 128);
const Color GREEN(0, 128, 0);
const Color TEAL(0, 128, 128);
const Color RED(128, 0, 0);
const Color PURPLE(128, 0, 128);
const Color YELLOW(128, 128, 0);
const Color GRAY(128, 128, 128);
const Color WHITE(255, 255, 255);
const Color LT_BLUE(0, 0, 255);
const Color LT_GREEN(0, 255, 0);
const Color LT_TEAL(0, 255, 255);
const Color LT_RED(255, 0, 0);
const Color LT_PURPLE(255, 0, 255);
const Color LT_YELLOW(255, 255, 0);
const Color LT_GRAY(192, 192, 192);

}

}

