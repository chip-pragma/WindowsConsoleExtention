#include "LineReader.h"

namespace wce {

LineReader::~LineReader() { }

bool LineReader::onConvert(std::string &srcLine, std::string &convertedValue) {
    convertedValue = srcLine;
    return true;
}

}