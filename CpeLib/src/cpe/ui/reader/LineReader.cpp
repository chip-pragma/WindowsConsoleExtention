#include "LineReader.h"

namespace cpe {


LineReader::LineReader(const IConverter<ReaderData<std::string>> &converter)
        : BaseReader<ReaderData<std::string>, std::string, ResultRead<std::string>(converter) {

};

bool LineReader::_LineConverter::convert(const std::string &lineValue, std::string &outValue,
                                         std::string &errorText) const {
    outValue = lineValue;
    return true;
}
}

