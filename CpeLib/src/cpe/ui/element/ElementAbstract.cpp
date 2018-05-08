#include "ElementAbstract.h"

namespace cpe {

void ElementAbstract::show() {
    show(term::window_size());
}

void ElementAbstract::show(const Point &maxSize) {
    TextCanvas canvas(maxSize);
    draw(canvas);
    canvas.output_to(std::cout);
}

}