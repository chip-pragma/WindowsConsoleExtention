#include "Color.h"

namespace wce {

Color::Color(uint8_t r, uint8_t g, uint8_t b) noexcept {
    this->red = r;
    this->green = g;
    this->blue = b;
}

bool Color::operator==(const Color &rhs) const {
    return red == rhs.red &&
           green == rhs.green &&
           blue == rhs.blue;
}

bool Color::operator!=(const Color &rhs) const {
    return !(rhs == *this);
}

}

