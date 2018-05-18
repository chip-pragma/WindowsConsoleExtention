#include "LineReader.h"

namespace cpe {

LineReader::LineReader() : ReaderBase<std::string>(mConverter) { }

bool LineReader::_LineConverter::convert(const std::string &lineValue, std::string &outValue,
                                         std::string &errorText) const {
    outValue = lineValue;
    return true;
}

}

