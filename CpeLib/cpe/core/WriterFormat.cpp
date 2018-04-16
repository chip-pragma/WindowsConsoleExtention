

#include "WriterFormat.h"


namespace cpe::core {

WriterFormat::WriterFormat() :
        _tabLength(4),
        _unfinished("...") {}

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

//
//  TODO Доделать применение формата к строке. Додумать, что делать при \n
//
std::string WriterFormat::apply(const std::string &src, uint32_t maxLength = 0) {
    /*std::string result;
    uint32_t lineLength = 0;
    for (char c : src) {
        switch (c) {
            case '\t':
                uint8_t factTab = _tabLength;
                if (maxLength != 0 && maxLength - lineLength)
                result += std::string(factTab, ' ');
            case '\n':
            case '\r':
                lineLength = 0;
            default:
                result += c;
        }
    }*/
}

}