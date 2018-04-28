#include <iostream>
#include <cpe/core/Terminal.h>

#include "script/TestScript.h"

using namespace cpe;

namespace {

// TODO Реализовать BindProperty без bind и BindProperty с возможностью задавать nullptr

}

int main() {
    term::setTitle("Текст консоли"_dos);
    term::setForeColor(Colors::WHITE);
    term::setBackColor(Colors::BLACK);

    term::pause();

    TestScript script;
    std::cout << "\nScript created:\n\t"
              << script.processor().state() << "\n\t";
    script.run();

    script.processor().state("It's changed 3!"_dos);
    std::cout << "\nState '()':\n\t"
              << script.processor().state() << "\n\t";
    script.run();

    term::pause();

    return 0;
}
