#include "Label.h"

namespace cpe {

Label::~Label() { }

const StyledText &Label::getText() const {
    return mText;
}

StyledText &Label::getText() {
    return mText;
}

void Label::onWrite(Buffer &buf) {
    buf.draw(this->getText());
}

}