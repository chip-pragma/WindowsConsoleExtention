#include "Label.h"

namespace wce {

Label::~Label() { }

const StyledText &Label::getText() const {
    return mText;
}

StyledText &Label::getTextRef() {
    return mText;
}

void Label::onWrite(Buffer &buf) {
    buf.draw(this->getTextRef());
}

}