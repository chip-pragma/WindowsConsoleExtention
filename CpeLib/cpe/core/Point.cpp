#include "cpe/Platform.h"
#include "Point.h"

namespace cpe {

Point::Point() noexcept {
    x = 0;
    y = 0;
}

Point::Point(int16_t x, int16_t y) noexcept {
    this->x = x;
    this->y = y;
}

Point::Point(const PlatformPoint &platformPoint) noexcept {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    x = platformPoint.X;
    y = platformPoint.Y;
#endif
}

PlatformPoint Point::toPlatform() const noexcept {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    COORD coord{
            .X = x,
            .Y = y
    };
    return coord;
#endif
}

Point &Point::operator+=(const Point &p1) noexcept {
    x += p1.x;
    y += p1.y;
    return *this;
}

Point Point::operator+(const Point &p1) noexcept {
    return Point(x + p1.x, y + p1.y);
}

Point &Point::operator-=(const Point &p1) noexcept {
    x -= p1.x;
    y -= p1.y;
    return *this;
}

Point Point::operator-(const Point &p1) noexcept {
    return Point(x - p1.x, y - p1.y);
}

Point &Point::operator*=(int16_t k) noexcept {
    x *= k;
    y *= k;
    return *this;
}

Point Point::operator*(int16_t k) noexcept {
    return Point(x * k, y * k);
}

}