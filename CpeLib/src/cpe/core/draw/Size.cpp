#include "Size.h"
#include "Point.h"

#include <sstream>

namespace cpe {

Size::Size() {
    mWidth = 0;
    mHeight = 0;
}

Size::Size(uint32_t w, uint32_t h) {
    mWidth = w;
    mHeight = h;
}

uint32_t Size::width() const {
    return mWidth;
}

void Size::width(uint32_t w) {
    mWidth = w;
}

uint32_t Size::height() const {
    return mHeight;
}

void Size::height(uint32_t h) {
    mHeight = h;
}

Point Size::to_point() const {
    return Point(mWidth, mHeight);
}

std::string Size::to_string() const {
    std::stringstream ss;
    ss << "(width=" << mWidth << "; height=" << mHeight << ")";
    return ss.str();
}

Size &Size::operator+=(const Size &p1) {
    mWidth += p1.mWidth;
    mHeight += p1.mHeight;
    return *this;
}

Size Size::operator+(const Size &p1) const {
    return Size(mWidth + p1.mWidth, mHeight + p1.mHeight);
}

Size &Size::operator-=(const Size &p1) {
    mWidth -= p1.mWidth;
    mHeight -= p1.mHeight;
    return *this;
}

Size Size::operator-(const Size &p1) const {
    return Size(mWidth - p1.mWidth, mHeight - p1.mHeight);
}

Size &Size::operator*=(uint32_t k) {
    mWidth *= k;
    mHeight *= k;
    return *this;
}

Size Size::operator*(uint32_t k) const {
    return Size(mWidth * k, mHeight * k);
}

Size &Size::operator/=(uint32_t k) {
    mWidth /= k;
    mHeight /= k;
    return *this;
}

Size Size::operator/(uint32_t k) const {
    return Size(mWidth / k, mHeight / k);
}

bool Size::operator==(const Size &size) const {
    return mWidth == size.mWidth &&
           mHeight == size.mHeight;
}

bool Size::operator!=(const Size &size) const {
    return !(size == *this);
}

}



