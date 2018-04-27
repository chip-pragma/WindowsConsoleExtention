#include <iostream>
#include <cpe/core/Terminal.h>

#include "script/TestScript.h"
#include "common.h"

using namespace cpe;

namespace {

// TODO Добавить обертку для необязательных значений свойств

}

int main() {
    term::setTitle("Текст консоли"_dos);
    term::setForeColor(Colors::WHITE);
    term::setBackColor(Colors::BLACK);

    TestScript script;
    auto proc = script.processor();
    proc->state->set(" ОПА, ПОМЕНЯЛИ 1! "_dos);
    script.run();

    term::pause();

    return 0;
}
