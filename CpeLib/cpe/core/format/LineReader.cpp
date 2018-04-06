#include "LineReader.h"

namespace cpe::core::format {

void LineReader::read(std::string &line, const OutputFormat &format) {
    _line = line;
    startRead();
    _outFormat = format;
}

void LineReader::onReceiveSymbol(const char &symbol) {
    //
    //  TODO вывод введенного текста. Учитывать удаление символов через \b и затирание последнего символа.
    //

    switch (symbol) {
        case '\n':
        case '\r':
            finishRead();
            return;
        case '\t':

        default:
            _line += symbol;

            break;
    }
}

void LineReader::onReceiveCommand(const KeyType &command) {

}

void LineReader::onReadingError() {

}

void LineReader::output() {

}


}