

#include "TextStyle.h"


namespace cpe::ui::style {

TextStyle::TextStyle(
        uint8_t tabLength,
        const std::string &unfinished)
        : _tabLength(tabLength), _unfinished(unfinished) {}

uint8_t TextStyle::getTabLength() const {
    return _tabLength;
}

const std::string &TextStyle::getUnfinished() const {
    return _unfinished;
}
}