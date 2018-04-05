

#include "OutputFormat.h"


namespace cpe::ui {

OutputFormat::OutputFormat() : _tabLength(4), _unfinished(L"...")
{}

uint8_t OutputFormat::getTabLength() const {
    return _tabLength;
}

void OutputFormat::setTabLength(uint8_t tabLength) {
    _tabLength = tabLength;
}

const std::wstring &OutputFormat::getUnfinished() const {
    return _unfinished;
}

void OutputFormat::setUnfinished(const std::wstring &unfinished) {
    _unfinished = unfinished;
}

}