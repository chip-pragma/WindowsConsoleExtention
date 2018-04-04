#include "Platform.h"

namespace cpe::core::platform {

namespace {

#if defined(CPE_PLATFORM_IS_WINDOWS)

namespace _winapi {

enum class ColorComponent : uint8_t {
    RED = 2,
    GREEN = 1,
    BLUE = 0
};

PlatformColor getColorComponentBit(uint8_t component, ColorComponent comp) {
    if (component < 64)
        return 0;
    else if (component <= 192)
        return (PlatformColor) 1 << (uint8_t) comp;
    else
        return (PlatformColor) (8u | (1u << (uint8_t) comp));
}

}

#endif

}

PlatformPoint toPlatformPoint(const Point &point) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    COORD coord{
            .X = point.x,
            .Y = point.y
    };
    return coord;
#endif
}

Point toCpePoint(const PlatformPoint &coord) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return Point(coord.X, coord.Y);
#endif
}

PlatformColor toPlatformColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    PlatformColor pc =
            _winapi::getColorComponentBit(color.getR(), _winapi::ColorComponent::RED)
            | _winapi::getColorComponentBit(color.getG(), _winapi::ColorComponent::GREEN)
            | _winapi::getColorComponentBit(color.getB(), _winapi::ColorComponent::BLUE);
//
//    if (color.getR())
//        pc |= 4u;
//    if (color.getG())
//        pc |= 2u;
//    if (color.getB())
//        pc |= 1u;
//    if (color.isIntensive())
//        pc |= 8u;

    return pc;
#endif
}

Color toCpeColor(const PlatformColor &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    const uint8_t MIN = 128u;
    const uint8_t PLUS = 127;
    auto i = MIN;
    if (((unsigned) color & 8u) == 8u)
        i += PLUS;
    Color c;
    if (((unsigned) color & 4u) == 4u)
        c.setR(i);
    if (((unsigned) color & 2u) == 2u)
        c.setG(i);
    if (((unsigned) color & 1u) == 1u)
        c.setB(i);

    return c;
#endif
}

}