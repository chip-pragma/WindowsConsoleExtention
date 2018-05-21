#include "TextColor.h"

#include <utility>

namespace cpe {

TextColor::TextColor() {

}

TextColor::TextColor(const std::optional<Color> fore, const std::optional<Color> back) {
    mFore = fore;
    mBack = back;
}

TextColor::TextColor(const TextColor &tc) {
    mFore = tc.mFore;
    mBack = tc.mBack;
}

TextColor::TextColor(TextColor &&tc) noexcept {
    mFore = tc.mFore;
    mBack = tc.mBack;
    tc.mFore = std::nullopt;
    tc.mBack = std::nullopt;
}

const std::optional<Color> &TextColor::foreground() const {
    return mFore;
}

std::optional<Color> &TextColor::foreground() {
    return mFore;
}

const std::optional<Color> &TextColor::background() const {
    return mBack;
}

std::optional<Color> &TextColor::background() {
    return mBack;
}

void TextColor::set(const TextColor &tc) {
    mFore = tc.mFore;
    mBack = tc.mBack;
}

TextColor &TextColor::operator=(const TextColor &tc) {
    mFore = tc.mFore;
    mBack = tc.mBack;
    return *this;
}

}