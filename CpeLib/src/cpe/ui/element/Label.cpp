#include "Label.h"

cpe::LabelData::~LabelData() { }

const cpe::StyledText &cpe::LabelData::text() const {
    return mText;
}

cpe::StyledText &cpe::LabelData::text() {
    return mText;
}

void cpe::Label::on_write(cpe::Buffer &buf) {
    buf.draw(data().text());
}
