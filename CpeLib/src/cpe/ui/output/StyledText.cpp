#include "StyledText.h"
#include "OutputHelper.h"
#include "cpe/core/Exception.h"

#include <algorithm>

namespace cpe {

StyledText::StyledText()
    : mColors(1) { }

StyledText::~StyledText() { }

const TextColor &StyledText::color() const {
    return mColors.back().color;
}

StyledText &StyledText::setColor(const TextColor &tColor) {
    if (mColors.back().color != tColor) {
        if (mColors.back().length != 0)
            mColors.emplace_back(tColor, mText.length());
        else
            mColors.back().color = tColor;
    }
    return *this;
}

StyledText &StyledText::resetColor() {
    setColor(TextColor());
    return *this;
}

StyledText &StyledText::append(const std::string &str) {
    mText += str;
    mColors.back().length += str.length();
    return *this;
}

StyledText &StyledText::append(const StyledText &sText) {
    mText += sText.mText;
    for (const auto &tsc : sText.mColors) {
        this->setColor(tsc.color);
        mColors.back().length += tsc.length;
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

void StyledText::outputTo(std::ostream &outStream) const {
    OutputHelper outHelp;
    outHelp.begin_colorized(outStream);
    for (size_t i = 0, j = 0; i < mText.length(); ++i) {
        if (mColors[j].position + mColors[j].length >= i)
            j++;
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