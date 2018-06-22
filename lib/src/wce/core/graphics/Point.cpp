#include "Point.h"

#include <sstream>

namespace wce {

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int32_t x, int32_t y) {
    this->x = x;
    this->y = y;
}

Point::Location Point::getLocation() const {
    int8_t result = PL_ZERO;
    if (x != 0) {
        result |= PL_X;
        if (x < 0)
            result |= PL_NEGATIVE_X;
    }
    if (y != 0) {
        result |= PL_Y;
        if (y < 0)
            result |= PL_NEGATIVE_Y;
    }
    return static_cast<Location>(result);
}

std::string Point::toString() const {
    std::stringstream ss;
    ss << "(x=" << x << "; y=" << y << ")";
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

Point &Point::operator+=(int32_t k) {
    x += k;
    y += k;
    return *this;
}

Point Point::operator+(int32_t k) const {
    return Point(x + k, y + k);
}

Point &Point::operator-=(int32_t k) {
    x -= k;
    y -= k;
    return *this;
}

Point Point::operator-(int32_t k) const {
    return Point(x - k, y - k);
}

Point &Point::operator*=(int32_t k) {
    x *= k;
    y *= k;
    return *this;
}

Point Point::operator*(int32_t k) const {
    return Point(x * k, y * k);
}

Point &Point::operator/=(int32_t k) {
    x /= k;
    y /= k;
    return *this;
}

Point Point::operator/(int32_t k) const {
    return Point(x / k, y / k);
}

bool Point::operator==(const Point &point) const {
    return x == point.x &&
           y == point.y;
}

bool Point::operator!=(const Point &point) const {
    return !(point == *this);
}

}