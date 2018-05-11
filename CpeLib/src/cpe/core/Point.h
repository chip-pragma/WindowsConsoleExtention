#pragma once

#include <string>

#include "cpe/platform.h"

namespace cpe {

/**
 * Двумерные координаты
 */
class Point {
public:
    int16_t x;
    int16_t y;

    Point();

    Point(int16_t x, int16_t y);

    explicit Point(const PlatformPoint &platformPoint);

    PlatformPoint to_platform() const;

    std::string to_string() const;

    Point &operator+=(const Point &p1);

    Point operator+(const Point &p1) const;

    Point &operator-=(const Point &p1);

    Point operator-(const Point &p1) const;

    Point &operator*=(int16_t k);

    Point operator*(int16_t k) const;

    Point &operator/=(int16_t k);

    Point operator/(int16_t k) const;

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;
};

}
