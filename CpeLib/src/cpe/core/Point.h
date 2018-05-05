#pragma once

#include "cpe/platform.h"

namespace cpe {

/**
 * Двумерные координаты
 */
class Point {
public:
    int16_t x;
    int16_t y;

    Point() noexcept;

    Point(int16_t x, int16_t y) noexcept;

    explicit Point(const PlatformPoint &platformPoint) noexcept;

    /**
     * Преобразует в платформозависимый тип представления координат
     */
    PlatformPoint toPlatform() const noexcept;

    Point &operator+=(const Point &p1) noexcept;

    Point operator+(const Point &p1) noexcept;

    Point &operator-=(const Point &p1) noexcept;

    Point operator-(const Point &p1) noexcept;

    Point &operator*=(int16_t k) noexcept;

    Point operator*(int16_t k) noexcept;

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;
};

}
