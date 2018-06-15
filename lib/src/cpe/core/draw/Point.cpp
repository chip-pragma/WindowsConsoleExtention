#include "Point.h"

#include <sstream>

namespace wce {

Point::Point() {
    mX = 0;
    mY = 0;
}

Point::Point(int32_t x, int32_t y) {
    this->mX = x;
    this->mY = y;
}

const int32_t &Point::getX() const {
    return mX;
}

int32_t &Point::getXRef() {
    return mX;
}

const int32_t &Point::getY() const {
    return mY;
}

int32_t &Point::getYRef() {
    return mY;
}

Point::Location Point::getLocation() const {
    int8_t result = PL_ZERO;
    if (mX != 0) {
        result |= PL_X;
        if (mX < 0)
            result |= PL_NEGATIVE_X;
    }
    if (mY != 0) {
        result |= PL_Y;
        if (mY < 0)
            result |= PL_NEGATIVE_Y;
    }
    return static_cast<Location>(result);
}

std::string Point::toString() const {
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