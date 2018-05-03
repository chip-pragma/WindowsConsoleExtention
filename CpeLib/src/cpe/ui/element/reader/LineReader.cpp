#include <cpe/ui/ControllerInterface.h>
#include "LineReader.h"

namespace cpe {

void LineReader::run(ControllerInterface &controller, Buffer &out) {
    std::string lineRead;
    auto valid = false;
    Buffer buf;
    buf.color(Colors::LT_YELLOW);
    while (!valid) {
        saveState();
        buf << getHint(controller);
        buf.flush();
        std::getline(std::cin, lineRead);
        valid = validateRead(controller, lineRead);
        clearBack();
    }

    out << foreColorMode << Colors::LT_RED
        << "Readed! Check buffer return.\n";
}

}



