#include "LineReader.h"

namespace cpe {

LineReader::LineReader(ViewInterface &parent,
                       PropertyWriteInterface<std::string> &readInto) : ElementAbstract(parent),
                                                                        ReaderAbstract(readInto) {}

LineReader::LineReader(ViewInterface &parent,
                       PropertyWriteInterface <std::string> &readInto,
                       const std::string &hint) : ElementAbstract(parent),
                                                  ReaderAbstract(readInto, hint) {}

Buffer & LineReader::run() {
    startRead();

    std::string lineRead;
    std::getline(std::cin, lineRead);

    finishRead(lineRead, false);

    mBuffer << foreColorMode << Colors::LT_RED << "Readed! Check buffer return.\n";

    return mBuffer;
}

}



