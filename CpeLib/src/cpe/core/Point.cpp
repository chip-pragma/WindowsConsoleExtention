#include "cpe/platform.h"
#include "Point.h"

#include <sstream>

namespace cpe {

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int16_t x, int16_t y) {
    this->x = x;
    this->y = y;
}

Point::Point(const PlatformPoint &platformPoint) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    x = platformPoint.X;
    y = platformPoint.Y;
#endif
}

PlatformPoint Point::to_platform() const {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    COORD coord{
            .X = x,
            .Y = y
    };
    return coord;
#endif
}

std::string Point::to_string() const {
    std::stringstream ss;
    ss << "(" << x << "; " << y << ")";
    return ss.str();
}

Point &Point::operator+=(const Point &p1) {
    x += p1.x;
    y += p1.y;
    return *this;
}

Point Point::operator+(const Point &p1) const {
    return Point(x + p1.x, y + p1.y);
}

Point &Point::operator-=(const Point &p1) {
    x -= p1.x;
    y -= p1.y;
    return *this;
}

Point Point::operator-(const Point &p1) const {
    return Point(x - p1.x, y - p1.y);
}

Point &Point::operator*=(int16_t k) {
    x *= k;
    y *= k;
    return *this;
}

Point Point::operator*(int16_t k) const {
    return Point(x * k, y * k);
}

Point &Point::operator/=(int16_t k) {
    x /= k;
    y /= k;
    return *this;
}

Point Point::operator/(int16_t k) const {
    return Point(x / k, y / k);
}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}

}