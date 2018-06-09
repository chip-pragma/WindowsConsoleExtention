#include "Label.h"

namespace cpe {

LabelData::~LabelData() {
    int i = 0;
}

const StyledText &LabelData::getText() const {
    return mText;
}

StyledText &LabelData::getText() {
    return mText;
}

void Label::onWrite(Buffer &buf) {
    buf.draw(getData().getText());
}

Label::~Label() {

}

}