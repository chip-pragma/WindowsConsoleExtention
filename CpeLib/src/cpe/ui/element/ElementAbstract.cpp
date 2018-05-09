#include "ElementAbstract.h"

namespace cpe {

void ElementAbstract::show() {
    auto ws = term::window_size();
    ws.x--;
    show(ws);
}

void ElementAbstract::show(const Point &maxSize) {
    TextCanvas canvas(maxSize);
    draw(canvas);
    canvas.output_to(std::cout);
}

}