

#include "WriterFormat.h"


namespace cpe {

uint8_t WriterFormat::getTabLength() const {
    return _tabLength;
}

void WriterFormat::setTabLength(uint8_t tabLength) {
    _tabLength = tabLength;
}

const std::string &WriterFormat::getUnfinished() const {
    return _unfinished;
}

void WriterFormat::setUnfinished(const std::string &unfinished) {
    _unfinished = unfinished;
}

}
