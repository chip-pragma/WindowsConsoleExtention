

#include "TextFormat.h"


namespace cpe {

uint8_t TextFormat::getTabLength() const {
    return _tabLength;
}

void TextFormat::setTabLength(uint8_t tabLength) {
    _tabLength = tabLength;
}

const std::string &TextFormat::getUnfinished() const {
    return _unfinished;
}

void TextFormat::setUnfinished(const std::string &unfinished) {
    _unfinished = unfinished;
}

}
