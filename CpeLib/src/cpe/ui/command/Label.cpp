#include "Label.h"

#include "cpe/ui/BufferManip.h"

namespace cpe {

Label::Label() {

}

Label::~Label() {

}

void *Label::run(Buffer &buf, std::vector<AReader *> &readers) {
    buf << setBack << style.back
        << setFore << style.fore
        << text;
}

}
