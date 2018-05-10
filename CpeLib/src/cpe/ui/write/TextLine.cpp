#include "TextLine.h"

namespace cpe {

TextLine::TextLine(size_type length) : std::vector<StyledChar>(length) {

}

TextLine::TextLine(const TextLine &line) : std::vector<StyledChar>(line) {
    mLast = line.mLast;
}

TextLine::size_type TextLine::get_last() const {
    return mLast;
}

void TextLine::set_as_unfinished(const std::string &unfinished) {
    auto length = this->size();
    auto unfLength = std::min(unfinished.length(), length);
    auto unfBegin = length - unfLength;
    auto begin = std::min(unfBegin, mLast);
    auto sym = this->at(begin);

    for (size_t i = begin, j = 0; j < unfLength; i++, j++) {
        at(i).character(unfinished[j]);
        at(i).style().foreground(sym.style().foreground());
        at(i).style().background(sym.style().background());
    }
}

StyledChar &TextLine::operator[](size_type index) {
    mLast = std::max(mLast, index);
    return this->at(index);
}

}



