#include "ElementBase.h"

#include <algorithm>

namespace cpe {

int16_t ElementBase::MAX_WIDTH = 70;
int16_t ElementBase::MAX_HEIGHT = 150;

void ElementBase::show() {
    auto ws = term::buffer_size();
    ws.x = std::min(--ws.x, MAX_WIDTH);
    ws.y = std::min(ws.y, MAX_HEIGHT);
    show(ws);
}

void ElementBase::show(const Point &maxSize) {
    TextCanvas canvas(maxSize);
    draw(canvas);
    canvas.output_to(std::cout);
}

}