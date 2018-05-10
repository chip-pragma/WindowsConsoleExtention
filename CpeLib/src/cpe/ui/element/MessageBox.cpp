#include "cpe/tool/Encoder.h"
#include "MessageBox.h"

namespace cpe {

const DualBorder &MessageBox::border_style() const {
    return mBorder.last_applied();
}

void MessageBox::border_style(const DualBorder &db) {
    mBorder.apply(db);
}

const std::string &MessageBox::caption() const {
    return mCaption;
}

void MessageBox::caption(const std::string &caption) {
    mCaption = caption;
}

const std::string &MessageBox::text() const {
    return mText;
}

void MessageBox::text(const std::string &text) {
    mText = text;
}

const Nullable<StyledChar> &MessageBox::icon() const {
    return mIcon;
}

Nullable<StyledChar> &MessageBox::icon() {
    return mIcon;
}

void MessageBox::icon(const Nullable<StyledChar> &icon) {
    mIcon.set(icon);
}

void MessageBox::draw(TextCanvas &canvas) {
    using Br = Border;

    std::string s;
    
    s += mBorder[Br::LT] + mBorder[Br::H] + mBorder[Br::HT] + mBorder[Br::H] + mBorder[Br::RT] + "\n";
    s += mBorder[Br::V] + " " + mBorder[Br::V] + " " + mBorder[Br::V] + "\n";
    s += mBorder[Br::VL] + mBorder[Br::H] + mBorder[Br::C] + mBorder[Br::H] + mBorder[Br::VR] + "\n";
    s += mBorder[Br::V] + " " + mBorder[Br::V] + " " + mBorder[Br::V] + "\n";
    s += mBorder[Br::LB] + mBorder[Br::H] + mBorder[Br::HB] + mBorder[Br::H] + mBorder[Br::RB] + "\n";

    // TODO преобразование из UTF-8 в DOS оптимизировать

    Encoder<Encoding::UTF8> encUtf8;
    Encoder<Encoding::CP866> encCp866;

    canvas << encCp866.to(encUtf8.from(s));
}

}



