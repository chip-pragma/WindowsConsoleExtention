#include "TextChar.h"

namespace cpe {

TextChar::TextChar(char c) : mChar(c) {}

TextChar::TextChar(char c, const TextCharStyle &style) : mChar(c),
                                                         mStyle(style) {}

TextChar::TextChar(const TextChar &c) {
    mChar = c.mChar;
    mStyle = c.mStyle;
}

TextChar::TextChar(TextChar &&c) noexcept {
    mChar = c.mChar;
    c.mChar = ' ';
    mStyle = c.mStyle;
    c.mStyle.foreground().set(nullptr);
    c.mStyle.background().set(nullptr);
}

TextChar::~TextChar() {

}

TextCharStyle &TextChar::style() {
    return mStyle;
}

void TextChar::style(const TextCharStyle &style) {
    mStyle = style;
}

char TextChar::getChar() const {
    return mChar;
}

void TextChar::setChar(char aChar) {
    mChar = aChar;
}

TextChar &TextChar::operator=(const TextChar &c) {
    mChar = c.mChar;
    mStyle = c.mStyle;
    return *this;
}


char TextChar::getAChar() const {
    return mChar;
}

void TextChar::setAChar(char aChar) {
    mChar = aChar;
}

}



