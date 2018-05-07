#include "TextChar.h"

namespace cpe {

TextChar::TextChar(char c) : mChar(c) {}

TextChar::TextChar(char c, const Color &fore, const Color &back) : mChar(c),
                                                                   mFore(Nullable<Color>(fore)),
                                                                   mBack(Nullable<Color>(back)) {}

TextChar::TextChar(const TextChar &c) {
    mChar = c.mChar;
    mFore = c.mFore;
    mBack = c.mBack;
}

TextChar::TextChar(TextChar &&c) noexcept {
    mChar = c.mChar;
    c.mChar = ' ';
    mFore = c.mFore;
    mBack = c.mBack;
    c.mFore.set(nullptr);
    c.mBack.set(nullptr);
}

TextChar::~TextChar() {

}

//region char

char TextChar::getChar() const {
    return mChar;
}

void TextChar::setChar(char aChar) {
    mChar = aChar;
}

//endregion

TextChar &TextChar::operator=(const TextChar &c) {
    mChar = c.mChar;
    mFore = c.mFore;
    mBack = c.mBack;
    return *this;
}

Nullable<Color> &TextChar::foreground() const {
    return mFore;
}

void TextChar::foreground(const Nullable<Color> &fore) {
    mFore = fore;
}

Nullable<Color> &TextChar::background() const {
    return mBack;
}

void TextChar::background(const Nullable<Color> &back) {
    mBack = back;
}


}



