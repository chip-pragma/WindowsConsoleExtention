#include "ElementBase.h"

#include <algorithm>

namespace cpe {

uint32_t ElementBase::MAX_WIDTH = 80;
uint32_t ElementBase::MAX_HEIGHT = 150;

void ElementBase::show() {
    auto ws = term::buffer_size();
    ws.width(std::min(ws.width() - 1, MAX_WIDTH));
    ws.height(std::min(ws.height(), MAX_HEIGHT));
    show(ws);
}

void ElementBase::show(const Size &maxSize) {
    TextCanvas canvas(maxSize);
    draw(canvas);
    canvas.output_to(std::cout);
}

}