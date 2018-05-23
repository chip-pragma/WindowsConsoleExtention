#include "StyledText.h"

#include "OutputHelper.h"

namespace cpe {

StyledText::StyledText(const StyledString &sStr) {
    push_back(sStr);
}

StyledText::StyledText(uint8_t tabLength, const std::string &unf)
        : mTabLength(tabLength),
          mUnfinished(unf) {

}

StyledText::~StyledText() { }

const uint8_t &StyledText::tab_length() const {
    return mTabLength;
}

uint8_t &StyledText::tab_length() {
    return mTabLength;
}

const std::string &StyledText::unfinished() const {
    return mUnfinished;
}

std::string &StyledText::unfinished() {
    return mUnfinished;
}

void StyledText::push_back(const StyledString &sStr) {
    for (const char &ch : sStr.str())
        _BaseVector::push_back(StyledChar(ch, sStr.color()));
}

void StyledText::push_back(const StyledText &sText) {
    for (const auto &ch : sText)
        _BaseVector::push_back(ch);
}

void StyledText::output_to(std::ostream &outStream) const {
    OutputHelper outHelp;
    outHelp.begin_colorized(outStream);
    for (const auto &c : *this) {
        outHelp.apply_color(c.color());
        outStream << c.character();
    }
    outHelp.end_colorized();
}

}