#include "TextColor.h"

#include <utility>

namespace wce {

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

const std::optional<Color> &TextColor::getFore() const {
    return mFore;
}

std::optional<Color> &TextColor::getForeRef() {
    return mFore;
}

const std::optional<Color> &TextColor::getBack() const {
    return mBack;
}

std::optional<Color> &TextColor::getBackRef() {
    return mBack;
}

TextColor &TextColor::operator=(const TextColor &tc) {
    mFore = tc.mFore;
    mBack = tc.mBack;
    return *this;
}

bool TextColor::operator==(const TextColor &rhs) const {
    return mFore == rhs.mFore &&
           mBack == rhs.mBack;
}

bool TextColor::operator!=(const TextColor &rhs) const {
    return !(rhs == *this);
}

}