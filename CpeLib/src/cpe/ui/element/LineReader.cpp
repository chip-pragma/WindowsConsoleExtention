#include "LineReader.h"

namespace cpe {

LineReader::~LineReader() {

}

bool LineReader::on_convert(std::string &srcLine, std::string &convertedValue) {
    convertedValue = srcLine;
    return true;
}

}