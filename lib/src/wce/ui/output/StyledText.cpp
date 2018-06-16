#include "StyledText.h"
#include "OutputHelper.h"
#include "wce/core/Exception.h"

#include <algorithm>

namespace wce {

StyledText::StyledText()
    : m_colors(1) { }

StyledText::~StyledText() { }

const TextColor &StyledText::getColor() const {
    return m_colors.back().color;
}

StyledText &StyledText::setColor(const TextColor &tColor) {
    if (m_colors.back().color != tColor) {
        if (m_colors.back().length != 0)
            m_colors.emplace_back(tColor, m_text.length());
        else
            m_colors.back().color = tColor;
    }
    return *this;
}

StyledText &StyledText::setFore(const ColorIndex &fore) {
    if (m_colors.back().color.foreground != fore) {
        if (m_colors.back().length != 0)
            m_colors.emplace_back(TextColor(fore, m_colors.back().color.background), m_text.length());
        else
            m_colors.back().color.foreground = fore;
    }
    return *this;
}

StyledText &StyledText::setBack(const ColorIndex &back) {
    if (m_colors.back().color.background != back) {
        if (m_colors.back().length != 0)
            m_colors.emplace_back(TextColor(m_colors.back().color.foreground, back), m_text.length());
        else
            m_colors.back().color.background = back;
    }
    return *this;
}

StyledText &StyledText::resetColor() {
    setColor(TextColor());
    return *this;
}

StyledText &StyledText::append(const std::string &str) {
    m_text += str;
    m_colors.back().length += str.length();
    return *this;
}

StyledText &StyledText::append(const StyledText &sText) {
    m_text += sText.m_text;
    auto prevColor = getColor();
    for (const auto &tsc : sText.m_colors) {
        this->setColor(tsc.color);
        m_colors.back().length += tsc.length;
    }
    this->setColor(prevColor);
    return *this;
}

StyledText &StyledText::append(const StyledChar &sChar) {
    m_text += sChar.character;
    auto prevColor = getColor();
    setColor(sChar.color);
    m_colors.back().length++;
    this->setColor(prevColor);
    return *this;
}

StyledText &StyledText::clear() {
    m_text.clear();
    m_colors = std::vector<_TextColorLine>(1);
    return *this;
}

size_t StyledText::getLength() const {
    return m_text.length();
}

StyledChar StyledText::at(size_t index) const {
    if (index < 0 ||
        index >= m_text.length())
        throw Exception("Out of range");

    auto c = m_text[index];
    TextColor clr;

    for (const auto &item : m_colors) {
        if (item.position > index) break;
        clr = item.color;
    }

    return StyledChar(c, clr);
}

void StyledText::outputTo(std::ostream &outStream) const {
    OutputHelper outHelp;
    outHelp.beginColorize(outStream);
    for (size_t i = 0, j = 0; i < m_text.length(); ++i) {
        if (m_colors[j].position + m_colors[j].length <= i)
            j++;
        outHelp.applyColor(m_colors[j].color);
        outStream << m_text[i];
    }
    outHelp.endColorize();
}

const std::string &StyledText::toString() const {
    return m_text;
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