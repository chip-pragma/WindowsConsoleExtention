#include "ElementBase.h"

#include <algorithm>

namespace cpe {

int32_t ElementBase::MAX_WIDTH = 80;
int32_t ElementBase::MAX_HEIGHT = 150;

void ElementBase::show() {
    auto ws = term::buffer_size();
    ws.x_crd(std::min(ws.x_crd() - 1, MAX_WIDTH));
    ws.y_crd(std::min(ws.y_crd(), MAX_HEIGHT));
    show(ws);
}

void ElementBase::show(const Point &maxSize) {
    Buffer canvas(maxSize);
    draw(canvas);
    canvas.output_to(std::cout);
}

}