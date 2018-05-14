#pragma once

#include <iostream>

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Point.h"
#include "cpe/ui/write/Buffer.h"

namespace cpe {

class ElementBase {
public:
    static int32_t MAX_WIDTH;
    static int32_t MAX_HEIGHT;

    virtual void draw(Buffer& cvs) = 0;

    virtual void show() final;

    virtual void show(const Point &maxSize) final;
};

}


