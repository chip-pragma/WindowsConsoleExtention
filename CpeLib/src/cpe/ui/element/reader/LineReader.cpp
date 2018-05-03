#include <cpe/ui/ControllerInterface.h>
#include "LineReader.h"

namespace cpe {

void LineReader::run(ControllerInterface &controller) {
    startRead(controller);

    std::string lineRead;
    std::getline(std::cin, lineRead);

    finishRead(controller, lineRead, true);

    mBuffer << foreColorMode << Colors::LT_RED << "Readed! Check buffer return.\n";
}

}



