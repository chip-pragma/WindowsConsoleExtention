#include "TextColor.h"

#include <utility>

namespace cpe {

TextColor::TextColor(const Nullable<Color> fore, const Nullable<Color> back) {
    mFore.set(fore);
    mBack.set(back);
}

TextColor::TextColor(const TextColor &tc) {
    mFore.set(tc.mFore);
    mBack.set(tc.mBack);
}

TextColor::TextColor(TextColor &&tc) noexcept {
    mFore.set(tc.mFore);
    mFore.set(tc.mBack);
    tc.mFore.set(nullptr);
    tc.mBack.set(nullptr);
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

void TextColor::set(const TextColor &tc) {
    mFore.set(tc.mFore);
    mFore.set(tc.mBack);
}

TextColor &TextColor::operator=(const TextColor &tc) {
    mFore.set(tc.mFore);
    mBack.set(tc.mBack);
    return *this;
}

}