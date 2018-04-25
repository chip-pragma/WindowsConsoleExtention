#include "Label.h"

#include "cpe/ui/BufferManip.h"

namespace cpe {

Label::Label() {
    propCreate(style.back);
    propCreate(style.fore);
    propCreate(text);
}

Label::~Label() {
    destroyProperties();
}

void Label::run() {
    Buffer buf;
    buf << setBack << style.back->get()
        << setFore << style.fore->get()
        << text->get();
    buf.flush();
}

}
