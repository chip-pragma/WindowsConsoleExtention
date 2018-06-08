#include "StyledText.h"
#include "OutputHelper.h"
#include "cpe/core/Exception.h"

#include <algorithm>

namespace cpe {

StyledText::StyledText()
    : mColors(1) { }

StyledText::~StyledText() { }

const TextColor &StyledText::getColor() const {
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

StyledText &StyledText::setFore(const Color &fore) {
    if (mColors.back().color.getFore() != fore) {
        if (mColors.back().length != 0)
            mColors.emplace_back(TextColor(fore, mColors.back().color.getBack()), mText.length());
        else
            mColors.back().color.getFore() = fore;
    }
    return *this;
}

StyledText &StyledText::setBack(const Color &back) {
    if (mColors.back().color.getBack() != back) {
        if (mColors.back().length != 0)
            mColors.emplace_back(TextColor(mColors.back().color.getFore(), back), mText.length());
        else
            mColors.back().color.getBack() = back;
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
    auto prevColor = getColor();
    for (const auto &tsc : sText.mColors) {
        this->setColor(tsc.color);
        mColors.back().length += tsc.length;
    }
    this->setColor(prevColor);
    return *this;
}

StyledText &StyledText::append(const StyledChar &sChar) {
    mText += sChar.getChar();
    auto prevColor = getColor();
    setColor(sChar.getColor());
    mColors.back().length++;
    this->setColor(prevColor);
    return *this;
}

StyledText &StyledText::clear() {
    mText.clear();
    mColors.clear();
    return *this;
}

size_t StyledText::getLength() const {
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
    outHelp.beginColorize(outStream);
    for (size_t i = 0, j = 0; i < mText.length(); ++i) {
        if (mColors[j].position + mColors[j].length <= i)
            j++;
        outHelp.applyColor(mColors[j].color);
        outStream << mText[i];
    }
    outHelp.endColorize();
}

const std::string &StyledText::toString() const {
    return mText;
}

StyledChar StyledText::operator[](size_t index) const {
    return at(index);
}

StyledText StyledText::operator+(const std::string &str) {
    return StyledText(*this).append(*this).append(str);
}

StyledText StyledText::operator+(const StyledText &sText) {
    return StyledText(*this).append(*this).append(sText);
}

StyledText StyledText::operator+(const StyledChar &sChar) {
    return StyledText(*this).append(*this).append(sChar);
}

StyledText &StyledText::operator+=(const std::string &str) {
    return append(str);
}

StyledText &StyledText::operator+=(const StyledText &sText) {
    return append(sText);
}

StyledText &StyledText::operator+=(const StyledChar &sChar) {
    return append(sChar);
}

StyledText operator+(const StyledChar &sc1, const StyledChar &sc2) {
    return StyledText().append(sc1).append(sc2);
}

}