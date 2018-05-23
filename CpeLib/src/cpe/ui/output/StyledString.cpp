#include "StyledString.h"
#include "OutputHelper.h"

namespace cpe {

StyledString::StyledString(const std::string &text) : mString(text) {

}

StyledString::StyledString(const std::string &text,
                           const TextColor &color) : mString(text),
                                                     mColor(color) {

}

const TextColor &StyledString::color() const {
    return mColor;
}

TextColor &StyledString::color() {
    return mColor;
}

const std::string &StyledString::str() const {
    return mString;
}

std::string &StyledString::str() {
    return mString;
}

void StyledString::output_to(std::ostream &outStream) const {
    OutputHelper outHelp;
    outHelp.begin_colorized(outStream);
    outHelp.apply_color(mColor);
    outStream << mString;
    outHelp.end_colorized();
}

}
