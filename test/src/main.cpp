#include <iostream>

#include <cpe/core/terminal.h>
#include <cpe/ui/write/TextCanvas.h>

#include "common.h"

using namespace cpe;

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();



    term::pause();

    return 0;
}
