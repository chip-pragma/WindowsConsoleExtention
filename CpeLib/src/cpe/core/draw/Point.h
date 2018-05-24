#pragma once

#include <string>
#include <cstdint>

namespace cpe {

class Point {
public:
    enum Dimension : int8_t {
        DIM_POINT = 0,
        DIM_X = 1,
        DIM_Y = 2,
        DIM_NEGATIVE_X = 4,
        DIM_NEGATIVE_Y = 8,
        DIM_SECTOR_I = DIM_X | DIM_Y,
        DIM_SECTOR_II = DIM_X | DIM_Y | DIM_NEGATIVE_X,
        DIM_SECTOR_III = DIM_X | DIM_Y | DIM_NEGATIVE_Y | DIM_NEGATIVE_X,
        DIM_SECTOR_VI = DIM_X | DIM_Y | DIM_NEGATIVE_Y,
    };

    Point();

    Point(int32_t x, int32_t y);

    const int32_t& x_crd() const;

    int32_t& x_crd();

    const int32_t& y_crd() const;

    int32_t& y_crd();

    Dimension dimension() const;

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
