#include "StyledText.h"
#include "OutputHelper.h"
#include "cpe/core/Exception.h"

#include <algorithm>

namespace cpe {

StyledText::StyledText()
    : mColors(1) { }

StyledText::~StyledText() { }

const TextColor &StyledText::text_color() const {
    return mColors.back().color;
}

StyledText &StyledText::color(const TextColor &tColor) {
    if (mColors.back().position < mText.length()
        && mColors.back().color != tColor)
        mColors.emplace_back(tColor, 0);
    else
        mColors.back().color = tColor;
    return *this;
}

StyledText &StyledText::reset_color() {
    color(TextColor());
    return *this;
}

StyledText &StyledText::append(const std::string &str) {
    mText += str;
    return *this;
}

StyledText &StyledText::append(const StyledText &sText) {
    mText += sText.mText;
    for (const auto &tsc : sText.mColors) {
        this->color(tsc.color);
        mColors.back().position += tsc.position;
    }
    return *this;
}

size_t StyledText::length() const {
    return mText.length();
}

StyledChar StyledText::at(size_t index) const {
    if (index < 0 ||
        index >= mText.length())
        throw Exception("Out of range");

    auto c = mText[index];
    TextColor clr;

    for (const auto &item : mColors) {
        if (item.position > index) break;
        clr = item.color;
    }

    return StyledChar(c, clr);
}

void StyledText::output_to(std::ostream &outStream) const {
    OutputHelper outHelp;
    outHelp.begin_colorized(outStream);

    // FIXME Вывод текста
    for (size_t i = 0, j = 0, k = 0; i < mText.length(); ++i, ++k) {
        if (mColors[j].position +=)
        outHelp.apply_color(mColors[j].color);
        outStream << mText[i];
    }
    outHelp.end_colorized();
}

const std::string &StyledText::to_string() const {
    return mText;
}

StyledChar StyledText::operator[](size_t index) const {
    return at(index);
}

}