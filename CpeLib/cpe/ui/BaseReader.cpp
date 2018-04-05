#include "BaseReader.h"

namespace cpe::ui {


void BaseReader::read() {
    for (; !_endRead;) {

    }
    _endRead = false;
}

void BaseReader::endRead() {
    _endRead = true;
}
}