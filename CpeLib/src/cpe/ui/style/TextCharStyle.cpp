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

const Nullable<Color> &TextCharStyle::foreground() const {
    return mFore;
}

Nullable<Color> &TextCharStyle::foreground() {
    return mFore;
}

const Nullable<Color> &TextCharStyle::background() const {
    return mBack;
}

Nullable<Color> &TextCharStyle::background() {
    return mBack;
}

TextCharStyle &TextCharStyle::operator=(const TextCharStyle &style) {
    mFore.set(style.mFore);
    mBack.set(style.mBack);
    return *this;
}

}