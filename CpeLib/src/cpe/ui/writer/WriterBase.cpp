#include "WriterBase.h"
#include "cpe/core/terminal.h"

namespace cpe {

WriterBase::~WriterBase() {

}

void WriterBase::output_to(std::ostream &outStream, const Point &size) {
    Buffer buf(size);
    this->draw(buf);
    buf.output_to(outStream);
}

}


