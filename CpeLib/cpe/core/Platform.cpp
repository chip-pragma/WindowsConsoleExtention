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

}