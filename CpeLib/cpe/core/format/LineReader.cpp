#include "LineReader.h"
#include "cpe/core/Console.h"

#include <iostream>

namespace cpe::core::format {

LineReader::LineReader() : BaseInput() {
}

void LineReader::read(std::string &line, const OutputFormat &format) {
    _line = &line;
    _outFormat = format;
    startRead();
}

void LineReader::onKeyRead(const char &symbol) {
//    std::cout << "[LineReader.Symbol: " << symbol << " ]\n";
    constexpr char keyCtrlBs = (31 & '\b');
    switch (symbol) {
        case '\n':
        case '\r':
            finishRead();
            break;
        case '\b':
            if (!_line->empty()) {
                _line->pop_back();
                std::cout << "\b \b";
            }
            break;
        case '\t':
            // TODO табуляция
            break;
        default:
            *_line += symbol;
            std::cout << symbol;
            break;
    }

    auto lastPos = console::getCursorPosition();
    console::setCursorPosition(Point(0, 0));
    std::cout << "[" << symbol << "]\t";
    console::setCursorPosition(lastPos);
}

void LineReader::onReadingError(uint32_t errCode) {
//    std::cout << "[LineReader.Error: " << errCode << " ]\n";
}


}