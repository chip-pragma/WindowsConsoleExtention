#pragma once

#include "Platform.h"

namespace cpe {

/**
 * Цвета, доступные в консоли
 */
class Color {
public:
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    Color() = default;

    Color(uint8_t r, uint8_t g, uint8_t b) noexcept;

    explicit Color(const PlatformColor &platformColor) noexcept;

    /**
     * Преобразует в платформозависимый тип представления цвета
     */
    PlatformColor toPlatform() const noexcept;

    bool operator==(const Color &rhs) const;

    bool operator!=(const Color &rhs) const;
};

/**
 * Предопределенные цвета
 */
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

