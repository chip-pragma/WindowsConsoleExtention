#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H

#include <cstdint>
#include <Windows.h>

namespace cpe::core {

/**
 * Двумерные координаты
 */
class Point {
public:
    Point();
    Point(int16_t x, int16_t y);

    int16_t x;
    int16_t y;

    Point operator +(const Point& p1);
};

}

#endif //PROJECT_POINT_H
