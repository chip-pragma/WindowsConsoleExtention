#pragma once

#include "Point.h"

// FEATURE доделать Rectangle

namespace cpe {

class Rectangle {
public:
    Rectangle() = default;

    Rectangle(Point pos, Point size);

private:
    Point mPosition;
    Point mSize;
};

}




