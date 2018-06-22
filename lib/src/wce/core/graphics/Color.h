#pragma once

#include <cstdint>

namespace wce {

class Color {
public:
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    Color() = default;

    Color(uint8_t r, uint8_t g, uint8_t b) noexcept;

    bool operator==(const Color &rhs) const;

    bool operator!=(const Color &rhs) const;
};

}

