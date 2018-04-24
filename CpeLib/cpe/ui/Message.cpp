#include "Message.h"

#include "BufferManip.h"

namespace cpe {

const std::string &Message::getCaption() const {
    return mCaption;
}

Message *Message::setCaption(const std::string &caption) {
    mCaption = caption;
    return this;
}

const std::string &Message::getText() const {
    return mText;
}

Message *Message::setText(const std::string &text) {
    mText = text;
    return this;
}

void Message::run() {
    Buffer buf;
    buf << setBack << Colors::BLUE
        << setFore << Colors::LT_TEAL
        << mText;
    buf.flush();
}

}
