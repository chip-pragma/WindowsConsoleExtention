#include "Message.h"

#include "BufferManip.h"

namespace cpe {

Message::Message() {
    createProperty(text);
    createProperty(caption);
}

Message::~Message() {
    destroyProperties();
}

void Message::run() {
    Buffer buf;
    buf << setBack << Colors::BLUE
        << setFore << Colors::LT_TEAL
        << text->get();
    buf.flush();
}

}
