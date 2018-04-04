#include "Color.h"

namespace cpe::core {

const Color Color::BLACK = Color(0, 0, 0);
const Color Color::BLUE = Color(0, 0, 128);
const Color Color::GREEN = Color(0, 128, 0);
const Color Color::TEAL = Color(0, 128, 128);
const Color Color::RED = Color(128, 0, 0);
const Color Color::PURPLE = Color(128, 0, 128);
const Color Color::YELLOW = Color(128, 128, 0);
const Color Color::GRAY = Color(128, 128, 128);
const Color Color::WHITE = Color(255, 255, 255);
const Color Color::LT_BLUE = Color(0, 0, 255);
const Color Color::LT_GREEN = Color(0, 255, 0);
const Color Color::LT_TEAL = Color(0, 255, 255);
const Color Color::LT_RED = Color(255, 0, 0);
const Color Color::LT_PURPLE = Color(255, 0, 255);
const Color Color::LT_YELLOW = Color(255, 255, 0);
const Color Color::LT_GRAY = Color(192, 192, 192);

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    setAll(r,g,b);
}

uint8_t Color::getR() const {
    return _r;
}

void Color::setR(unsigned char r) {
    _r = r;
}

uint8_t Color::getG() const {
    return _g;
}

void Color::setG(unsigned char g) {
    _g = g;
}

uint8_t Color::getB() const {
    return _b;
}

void Color::setB(unsigned char b) {
    _b = b;
}

void Color::setAll(uint8_t r, uint8_t g, uint8_t b) {
    _r = r;
    _g = g;
    _b = b;
}

bool Color::isIntensive() const {
    static const int MIN = 191;
    return (_r > MIN || _g > MIN || _b > MIN);
}

Color::Color() {
    _r = 0;
    _g = 0;
    _b = 0;
}

}