#include "ElementBase.h"

namespace cpe {

void ElementBase::show() {
    auto ws = term::window_size();
    ws.x--;
    show(ws);
}

void ElementBase::show(const Point &maxSize) {
    TextCanvas canvas(maxSize);
    draw(canvas);
    canvas.output_to(std::cout);
}

}