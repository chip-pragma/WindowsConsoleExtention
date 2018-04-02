#include "Point.h"

namespace cpe::core {

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int16_t x, int16_t y) {
    this->x = x;
    this->y = y;
}

Point Point::operator+(const Point &p1) {
    return Point(
            p1.x + x,
            p1.y + y);
}

}