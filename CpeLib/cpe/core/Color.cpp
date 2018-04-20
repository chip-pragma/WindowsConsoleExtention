#include "Color.h"

namespace cpe {

Color::Color() noexcept {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) noexcept {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(const PlatformColor &platformColor) noexcept {
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
            _winapi::getColorComponentBit(r, _winapi::BitColorComponent::RED)
            | _winapi::getColorComponentBit(g, _winapi::BitColorComponent::GREEN)
            | _winapi::getColorComponentBit(b, _winapi::BitColorComponent::BLUE);
    return pc;
#endif
}

bool Color::isIntensive() const noexcept {
    static const int MIN = 191;
    return (r > MIN || g > MIN || b > MIN);
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

