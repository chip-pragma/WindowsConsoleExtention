#include "Message.h"

#include "cpe/ui/BufferManip.h"

namespace cpe {

Message::Message() {
    propCreate(text, &Message::textSet, &Message::textGet);
    propCreate(caption);
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

void Message::textSet(const std::string &value) {
    Buffer buf;
    buf << "[SETTER]";
    buf.flush();
    propValue<std::string>(text) = value;
}

const std::string &Message::textGet() {
    Buffer buf;
    buf << "[GETTER]";
    buf.flush();;
    return propValue<std::string>(text);
}

}
