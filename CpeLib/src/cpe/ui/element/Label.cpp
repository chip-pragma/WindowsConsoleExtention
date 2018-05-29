#include "Label.h"

cpe::LabelData::~LabelData() { }

const cpe::StyledText &cpe::LabelData::getText() const {
    return mText;
}

cpe::StyledText &cpe::LabelData::getText() {
    return mText;
}

void cpe::Label::onWrite(cpe::Buffer &buf) {
    buf.draw(getData().getText());
}
