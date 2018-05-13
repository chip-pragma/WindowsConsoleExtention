#pragma once

#include <iostream>

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Point.h"
#include "cpe/ui/write/TextCanvas.h"

namespace cpe {

class ElementBase {
public:
    static int32_t MAX_WIDTH;
    static int32_t MAX_HEIGHT;

    virtual void draw(TextCanvas& canvas) = 0;

    virtual void show() final;

    virtual void show(const Point &maxSize) final;
};

}


