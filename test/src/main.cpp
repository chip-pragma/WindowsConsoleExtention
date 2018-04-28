#include <iostream>
#include <cpe/core/Terminal.h>

#include "script/TestScript.h"
#include "common.h"

using namespace cpe;

namespace {

// TODO Реализовать Property без sync и Property с возможностью задавать nullptr

}

int main() {
    term::setTitle("Текст консоли"_dos);
    term::setForeColor(Colors::WHITE);
    term::setBackColor(Colors::BLACK);

    TestScript script;
    auto &proc = script.processor();
    proc.state = " ОПА, ПОМЕНЯЛИ 1! "_dos;
    std::string str = proc.state;
    proc.state->clear();
    script.run();

    term::pause();

    return 0;
}
