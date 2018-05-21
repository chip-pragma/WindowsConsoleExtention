#include "StyledChar.h"
#include "Buffer.h"

#include <utility>

namespace cpe {

StyledChar::StyledChar() {

}

StyledChar::StyledChar(char c) : mChar(c) {}

StyledChar::StyledChar(char c, const TextColor &color) : mChar(c), mColor(color) {}

StyledChar::StyledChar(const StyledChar &sch) {
    mChar = sch.mChar;
    mColor = sch.mColor;
}

StyledChar::StyledChar(StyledChar &&sch) noexcept {
    mChar = sch.mChar;
    mColor = sch.mColor;
}

const TextColor &StyledChar::color() const {
    return mColor;
}

TextColor &StyledChar::color() {
    return mColor;
}

void StyledChar::color(const TextColor &color) {
    mColor = color;
}

char StyledChar::character() const {
    return mChar;
}

void StyledChar::character(char aChar) {
    mChar = aChar;
}

StyledChar &StyledChar::operator=(const StyledChar &sch) {
    mChar = sch.mChar;
    mColor = sch.mColor;
    return *this;
}

}



