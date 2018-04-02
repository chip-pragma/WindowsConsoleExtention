#include "Color.h"

namespace cpe::core {

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
    static const int MIN = 127;
    return (_r > MIN || _g > MIN || _b > MIN);
}

Color::Color() {
    _r = 0;
    _g = 0;
    _b = 0;
}

}