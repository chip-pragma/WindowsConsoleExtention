

#include "TextFormat.h"


namespace cpe::ui::style {

TextFormat::TextFormat() : _tabLength(4), _unfinished("...")
{}

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

Encoder &TextFormat::getInputEncoder() const {
    return _inputEncoder;
}

void TextFormat::setInputEncoder(Encoder &inputEncoder) {
    _inputEncoder = inputEncoder;
}

Encoder &TextFormat::getOutputEncoder() const {
    return _outputEncoder;
}

void TextFormat::setOutputEncoder(Encoder &outputEncoder) {
    _outputEncoder = outputEncoder;
}

}