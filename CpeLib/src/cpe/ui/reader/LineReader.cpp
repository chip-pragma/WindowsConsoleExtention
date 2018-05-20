#include "LineReader.h"

namespace cpe {

LineReader::LineReader()
        : ReaderBase<std::string, ReaderInitializer, ResultRead<std::string>>(mConverter) { }

ReaderInitializer LineReader::make_initializer() {
    return ReaderInitializer(static_cast<ReaderStyleBase &>(*this));
}

bool LineReader::_LineConverter::convert(const std::string &lineValue, std::string &outValue,
                                         std::string &errorText) const {
    outValue = lineValue;
    return true;
}

}

