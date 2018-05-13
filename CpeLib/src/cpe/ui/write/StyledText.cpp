#include "StyledText.h"


namespace cpe {

StyledText::StyledText(const std::string &text) : mText(text) {

}

StyledText::StyledText(const std::string &text,
                       const TextColor &color) : mText(text),
                                                 mColor(color) {

}

StyledText::StyledText(const std::string &text,
                       const TextColor &color,
                       uint8_t tabLength,
                       const std::string &unf) : mText(text),
                                                 mColor(color),
                                                 mTabLength(tabLength),
                                                 mUnfinished(unf) {

}

const TextColor &StyledText::color() const {
    return mColor;
}

TextColor &StyledText::color() {
    return mColor;
}

void StyledText::color(const TextColor &color) {
    mColor = color;
}

const std::string &StyledText::text() const {
    return mText;
}

std::string &StyledText::text() {
    return mText;
}

void StyledText::text(const std::string &text) {
    mText = text;
}

uint8_t StyledText::tab_length() const {
    return mTabLength;
}

void StyledText::tab_length(uint8_t tabLength) {
    mTabLength = tabLength;
}

const std::string &StyledText::unfinished() const {
    return mUnfinished;
}

void StyledText::unfinished(const std::string &unfinished) {
    mUnfinished = unfinished;
}

}
