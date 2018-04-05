

#include "WriterFormat.h"


namespace cpe::ui::style {

WriterFormat::WriterFormat() : _tabLength(4), _unfinished(L"...")
{}

uint8_t WriterFormat::getTabLength() const {
    return _tabLength;
}

void WriterFormat::setTabLength(uint8_t tabLength) {
    _tabLength = tabLength;
}

const std::wstring &WriterFormat::getUnfinished() const {
    return _unfinished;
}

void WriterFormat::setUnfinished(const std::wstring &unfinished) {
    _unfinished = unfinished;
}

}