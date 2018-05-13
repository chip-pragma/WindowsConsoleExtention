#include "TextColor.h"

#include <utility>

namespace cpe {

TextColor::TextColor(const Nullable<Color> fore, const Nullable<Color> back) {
    mFore.set(fore);
    mBack.set(back);
}

TextColor::TextColor(const TextColor &style) {
    mFore.set(style.mFore);
    mBack.set(style.mBack);
}

TextColor::TextColor(TextColor &&style) noexcept {
    mFore.set(style.mFore);
    mFore.set(style.mBack);
    style.mFore.set(nullptr);
    style.mBack.set(nullptr);
}

const Nullable<Color> &TextColor::foreground() const {
    return mFore;
}

Nullable<Color> &TextColor::foreground() {
    return mFore;
}

const Nullable<Color> &TextColor::background() const {
    return mBack;
}

Nullable<Color> &TextColor::background() {
    return mBack;
}

TextColor &TextColor::operator=(const TextColor &style) {
    mFore.set(style.mFore);
    mBack.set(style.mBack);
    return *this;
}

}