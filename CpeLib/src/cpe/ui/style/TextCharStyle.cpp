#include "TextCharStyle.h"

#include <utility>

namespace cpe {

TextCharStyle::TextCharStyle(const Nullable<Color> fore, const Nullable<Color> back) {
    mFore.set(fore);
    mBack.set(back);
}

TextCharStyle::TextCharStyle(const TextCharStyle &style) {
    mFore.set(style.mFore);
    mBack.set(style.mBack);
}

TextCharStyle::TextCharStyle(TextCharStyle &&style) noexcept {
    mFore.set(style.mFore);
    mFore.set(style.mBack);
    style.mFore.set(nullptr);
    style.mBack.set(nullptr);
}

const Nullable<Color> &TextCharStyle::get_foreground() const {
    return mFore;
}

Nullable<Color> &TextCharStyle::mod_foreground() {
    return mFore;
}

void TextCharStyle::set_foreground(const Nullable<Color> &fore) {
    mFore.set(fore);
}

const Nullable<Color> &TextCharStyle::get_background() const {
    return mBack;
}

Nullable<Color> &TextCharStyle::mod_background() {
    return mBack;
}

void TextCharStyle::set_background(const Nullable<Color> &back) {
    mBack.set(back);
}

TextCharStyle &TextCharStyle::operator=(const TextCharStyle &style) {
    mFore.set(style.mFore);
    mBack.set(style.mBack);
    return *this;
}

}