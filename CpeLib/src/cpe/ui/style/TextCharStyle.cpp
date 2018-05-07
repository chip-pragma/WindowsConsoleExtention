#include "TextCharStyle.h"

namespace cpe {

TextCharStyle::TextCharStyle(Nullable<Color> fore, Nullable<Color> back) {
    mFore = fore;
    mBack = back;
}

Nullable<Color> &TextCharStyle::foreground() const {
    return mFore;
}

void TextCharStyle::foreground(const Nullable<Color> &fore) {
    mFore = fore;
}

Nullable<Color> &TextCharStyle::background() const {
    return mBack;
}

void TextCharStyle::background(const Nullable<Color> &back) {
    mBack = back;
}

TextCharStyle &TextCharStyle::operator=(const TextCharStyle &style) {
    mFore = style.mFore;
    mBack = style.mBack;
    return *this;
}

}