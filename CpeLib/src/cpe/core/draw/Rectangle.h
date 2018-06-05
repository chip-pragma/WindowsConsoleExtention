#pragma once

#include "Point.h"

// QUEST доделать Rectangle

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




