#include "Point.h"
#include "Size.h"

#include <sstream>

namespace cpe {

Point::Point() {
    mX = 0;
    mY = 0;
}

Point::Point(int32_t x, int32_t y) {
    this->mX = x;
    this->mY = y;
}

int32_t Point::coord_x() const {
    return mX;
}

void Point::coord_x(int32_t x) {
    mX = x;
}

int32_t Point::coord_y() const {
    return mY;
}

void Point::coord_y(int32_t y) {
    mY = y;
}

Size Point::to_size() const {
    return Size(static_cast<uint32_t>(mX),
                static_cast<uint32_t>(mY));
}

std::string Point::to_string() const {
    std::stringstream ss;
    ss << "(x=" << mX << "; y=" << mY << ")";
    return ss.str();
}

Point &Point::operator+=(const Point &p1) {
    mX += p1.mX;
    mY += p1.mY;
    return *this;
}

Point Point::operator+(const Point &p1) const {
    return Point(mX + p1.mX, mY + p1.mY);
}

Point &Point::operator-=(const Point &p1) {
    mX -= p1.mX;
    mY -= p1.mY;
    return *this;
}

Point Point::operator-(const Point &p1) const {
    return Point(mX - p1.mX, mY - p1.mY);
}

Point &Point::operator+=(int32_t k) {
    mX += k;
    mY += k;
    return *this;
}

Point Point::operator+(int32_t k) const {
    return Point(mX + k, mY + k);
}

Point &Point::operator-=(int32_t k) {
    mX -= k;
    mY -= k;
    return *this;
}

Point Point::operator-(int32_t k) const {
    return Point(mX - k, mY - k);
}

Point &Point::operator*=(int32_t k) {
    mX *= k;
    mY *= k;
    return *this;
}

Point Point::operator*(int32_t k) const {
    return Point(mX * k, mY * k);
}

Point &Point::operator/=(int32_t k) {
    mX /= k;
    mY /= k;
    return *this;
}

Point Point::operator/(int32_t k) const {
    return Point(mX / k, mY / k);
}

bool Point::operator==(const Point &point) const {
    return mX == point.mX &&
           mY == point.mY;
}

bool Point::operator!=(const Point &point) const {
    return !(point == *this);
}

}