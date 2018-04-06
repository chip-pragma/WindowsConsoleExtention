#include <iostream>
#include "LineReader.h"

namespace cpe::core::format {

LineReader::LineReader() : BaseOutput() {
}

void LineReader::read(std::string &line, const OutputFormat &format) {
    _line = &line;
    _outFormat = format;
    startRead();
}

void LineReader::onReceiveSymbol(const char &symbol) {
//    std::cout << "[LineReader.Symbol: " << symbol << " ]\n";
    switch (symbol) {
        case '\n':
        case '\r':
            finishRead();
            return;
        case '\b':
            if (!_line->empty())
                _line->pop_back();
            break;
        case '\t':
            // TODO табуляция
            break;
        default:
            *_line += symbol;
            break;
    }
}

void LineReader::onReceiveCommand(const KeyType &command) {
//    std::cout << "[LineReader.Command: " << (int)command << " ]\n";
}

void LineReader::onReadingError(uint32_t errCode) {
//    std::cout << "[LineReader.Error: " << errCode << " ]\n";
}

void LineReader::output() {

}


}