#include <cpe/ui/ControllerInterface.h>
#include "LineReader.h"

namespace cpe {

void LineReader::run(ControllerInterface &controller, TextCanvas &out) {
    std::string lineRead;
    TextCanvas buf;
    std::cout << buf;
    buf.width(nullptr);

    buf.color(Colors::LT_YELLOW);
    auto valid = false;
    while (!valid) {
        saveState();

        buf << getHint(controller);
        buf.flush();
        std::getline(std::cin, lineRead);
        valid = applyValueRead(controller, lineRead);

        clearBack();
    }

    out.color(Colors::LT_RED);
    out << "Readed! Check buffer return.\n";
}

}



