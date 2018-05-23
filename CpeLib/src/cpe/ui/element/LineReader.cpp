#include "LineReader.h"

namespace cpe {

bool LineReader::on_convert(std::string &srcLine, std::string &convertedValue) {
    convertedValue = srcLine;
    return true;
}

}