#include "Color.h"

namespace cpe {

Color::Color(uint8_t r, uint8_t g, uint8_t b) noexcept {
    this->mRed = r;
    this->mGreen = g;
    this->mBlue = b;
}

uint8_t Color::red() const {
    return mRed;
}

void Color::red(uint8_t r) {
    mRed = r;
}

uint8_t Color::green() const {
    return mGreen;
}

void Color::green(uint8_t g) {
    mGreen = g;
}

uint8_t Color::blue() const {
    return mBlue;
}

void Color::blue(uint8_t b) {
    mBlue = b;
}

bool Color::operator==(const Color &rhs) const {
    return mRed == rhs.mRed &&
           mGreen == rhs.mGreen &&
           mBlue == rhs.mBlue;
}

bool Color::operator!=(const Color &rhs) const {
    return !(rhs == *this);
}


namespace Colors {

const Color BLACK(0, 0, 0);
const Color GRAY(64, 64, 64);  // Not work on WinApi
const Color BLUE(0, 0, 128);
const Color GREEN(0, 128, 0);
const Color TEAL(0, 128, 128);
const Color RED(128, 0, 0);
const Color PURPLE(128, 0, 128);
const Color YELLOW(128, 128, 0);
const Color LT_GRAY(192, 192, 192);
const Color LT_BLUE(0, 0, 255);
const Color LT_GREEN(0, 255, 0);
const Color LT_TEAL(0, 255, 255);
const Color LT_RED(255, 0, 0);
const Color LT_PURPLE(255, 0, 255);
const Color LT_YELLOW(255, 255, 0);
const Color WHITE(255, 255, 255);

}

}

