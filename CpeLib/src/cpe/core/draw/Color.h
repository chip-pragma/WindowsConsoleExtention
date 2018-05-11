#pragma once

#include <cstdint>

namespace cpe {

class Color {
public:
    Color() = default;

    Color(uint8_t r, uint8_t g, uint8_t b) noexcept;

    uint8_t red() const;

    void red(uint8_t r);

    uint8_t green() const;

    void green(uint8_t g);

    uint8_t blue() const;

    void blue(uint8_t b);

    bool operator==(const Color &rhs) const;

    bool operator!=(const Color &rhs) const;

protected:
    uint8_t mRed = 0;
    uint8_t mGreen = 0;
    uint8_t mBlue = 0;

};

namespace Colors {

extern const Color BLACK;
extern const Color BLUE;
extern const Color GREEN;
extern const Color TEAL;
extern const Color RED;
extern const Color PURPLE;
extern const Color YELLOW;
extern const Color GRAY;
extern const Color WHITE;
extern const Color LT_BLUE;
extern const Color LT_GREEN;
extern const Color LT_TEAL;
extern const Color LT_RED;
extern const Color LT_PURPLE;
extern const Color LT_YELLOW;
extern const Color LT_GRAY;

}

}

