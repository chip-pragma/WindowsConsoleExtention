#include "TextLine.h"

namespace cpe {

TextLine::TextLine(size_type length) : std::vector<TextChar>(length) {

}

TextLine::TextLine(const TextLine &line) : std::vector<TextChar>(line) {
    mLast = line.mLast;
}

TextLine::size_type TextLine::getLast() const {
    return mLast;
}

void TextLine::setAsUnfinished(const std::string &unfinished) {
    auto length = this->size();
    auto unfLength = std::min(unfinished.length(), length);
    auto unfBegin = length - unfLength;
    auto begin = std::min(unfBegin, mLast);
    auto sym = this->at(begin);

    for (size_t i = begin, j = 0; j < unfLength; i++, j++) {
        at(i).setChar(unfinished[j]);
        at(i).style().set_foreground(sym.style().mod_foreground());
        at(i).style().set_background(sym.style().mod_background());
    }
}

TextChar &TextLine::operator[](size_type index) {
    mLast = std::max(mLast, index);
    return this->at(index);
}

}



