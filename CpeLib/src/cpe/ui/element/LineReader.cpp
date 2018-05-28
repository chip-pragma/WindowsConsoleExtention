#include "LineReader.h"

namespace cpe {

LineReader::~LineReader() {

}

bool LineReader::onConvert(std::string &srcLine, std::string &convertedValue) {
    convertedValue = srcLine;
    return true;
}

}