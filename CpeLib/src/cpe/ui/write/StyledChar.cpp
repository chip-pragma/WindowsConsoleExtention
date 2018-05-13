#include "StyledChar.h"
#include "Buffer.h"

namespace cpe {

StyledChar::StyledChar(char c) : mChar(c) {}

StyledChar::StyledChar(char c, const TextColor &color) : mChar(c), mColor(color) {}

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

}



