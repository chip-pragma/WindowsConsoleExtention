#include "StyledChar.h"
#include "Buffer.h"

#include <utility>

namespace cpe {

StyledChar::StyledChar() { }

StyledChar::StyledChar(char c)
    : mChar(c) { }

StyledChar::StyledChar(char c, const TextColor &color)
    : mChar(c), mColor(color) {}

StyledChar::StyledChar(const StyledChar &sch) {
    mChar = sch.mChar;
    mColor = sch.mColor;
}

StyledChar::StyledChar(StyledChar &&sch) noexcept {
    mChar = sch.mChar;
    mColor = sch.mColor;
}

const TextColor &StyledChar::getColor() const {
    return mColor;
}

TextColor &StyledChar::getColorRef() {
    return mColor;
}

char StyledChar::getChar() const {
    return mChar;
}

void StyledChar::setChar(char aChar) {
    mChar = aChar;
}

StyledChar &StyledChar::operator=(const StyledChar &sch) {
    mChar = sch.mChar;
    mColor = sch.mColor;
    return *this;
}

}



