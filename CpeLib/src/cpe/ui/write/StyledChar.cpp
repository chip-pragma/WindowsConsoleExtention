#include "StyledChar.h"

namespace cpe {

StyledChar::StyledChar(char c) : mChar(c) {}

StyledChar::StyledChar(char c, const TextCharStyle &style) : mChar(c),
                                                         mStyle(style) {}

StyledChar::StyledChar(const StyledChar &c) {
    mChar = c.mChar;
    mStyle = c.mStyle;
}

StyledChar::StyledChar(StyledChar &&c) noexcept {
    mChar = c.mChar;
    c.mChar = ' ';
    mStyle = c.mStyle;
    c.mStyle.foreground().set(nullptr);
    c.mStyle.background().set(nullptr);
}

StyledChar::~StyledChar() {

}

const TextCharStyle &StyledChar::style() const{
    return mStyle;
}

TextCharStyle &StyledChar::style() {
    return mStyle;
}

void StyledChar::style(const TextCharStyle &style) {
    mStyle = style;
}

char StyledChar::character() const {
    return mChar;
}

void StyledChar::character(char aChar) {
    mChar = aChar;
}

StyledChar &StyledChar::operator=(const StyledChar &c) {
    mChar = c.mChar;
    mStyle = c.mStyle;
    return *this;
}

}



