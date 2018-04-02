#include "Platform.h"

namespace cpe::core::platform {

PlatformPoint toPlatformPoint(const Point &point) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return COORD{
            .X = point.x,
            .Y = point.y
    };
#endif
}

Point toCpePoint(const PlatformPoint &coord) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return Point(coord.X, coord.Y);
#endif
}

PlatformColor toPlatformColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    PlatformColor pc = 0;

    if (color.getR())
        pc |= 4u;
    if (color.getG())
        pc |= 2u;
    if (color.getB())
        pc |= 1u;
    if (color.isIntensive())
        pc |= 8u;

    return pc;
#endif
}

Color toCpeColor(const PlatformColor &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    const uint8_t MIN = 127u;
    const uint8_t PLUS = 128;
    auto i = MIN;
    if (((unsigned)color & 8u) == 8u)
        i += PLUS;
    Color c;
    if (((unsigned)color & 4u) == 4u)
        c.setR(i);
    if (((unsigned)color & 2u) == 2u)
        c.setG(i);
    if (((unsigned)color & 1u) == 1u)
        c.setB(i);

    return c;
#endif
}

}