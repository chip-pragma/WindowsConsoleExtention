#pragma once

#include <string>

namespace cpe {

class Size;

class Point {
public:
    Point();

    Point(int32_t x, int32_t y);

    int32_t coord_x() const;

    void coord_x(int32_t x);

    int32_t coord_y() const;

    void coord_y(int32_t y);

    Size to_size() const;

    std::string to_string() const;

    Point &operator+=(const Point &p1);

    Point operator+(const Point &p1) const;

    Point &operator-=(const Point &p1);

    Point operator-(const Point &p1) const;

    Point &operator+=(int32_t k);

    Point operator+(int32_t k) const;

    Point &operator-=(int32_t k);

    Point operator-(int32_t k) const;

    Point &operator*=(int32_t k);

    Point operator*(int32_t k) const;

    Point &operator/=(int32_t k);

    Point operator/(int32_t k) const;

    bool operator==(const Point &point) const;

    bool operator!=(const Point &point) const;

protected:
    int32_t mX;
    int32_t mY;
};

}
