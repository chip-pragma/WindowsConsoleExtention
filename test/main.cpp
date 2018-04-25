#include <iostream>
#include <vector>
#include <cmath>
#include <cpe/ui/command/Label.h>

#include "cpe/core/Encoder.h"
#include "cpe/ui/AScript.h"

#include "TestScript.h"

using namespace cpe;

namespace {

Encoder<Encoding::UTF8> encUtf8;
Encoder<Encoding::CP866> encCp866;

std::string encode(const std::string &src) {
    return encCp866.to(encUtf8.from(src));
}

}

int main() {
    term::setTitle(L"Текст консоли");
    term::setForeColor(Colors::WHITE);
    term::setBackColor(Colors::BLACK);

    std::cout << encode("Кодировка вывода: ") << term::getWriterCp() << "\n";
    std::cout << encode("Кодировка ввода: ") << term::getWriterCp() << std::endl;
    std::cout << encode("\u255F\n\n");

    term::pause();

    TestScript script;
    auto proc = script.processor();
    std::cout << "1. " << proc->state->get() << "\n";
    proc->state->set(proc->state->get() + encode(" ОПА, ПОМЕНЯЛИ 1!"));
    std::cout << "2. " << proc->state->get() << "\n";
    proc->state->set(encode(" ОПА, ПОМЕНЯЛИ 2!"));
    std::cout << "3. " << proc->state->get() << "\n";
    proc->state->set(proc->state->get() + encode(" ОПА, ПОМЕНЯЛИ 3!"));
    std::cout << "4. " << proc->state->get() << "\n";
    script.run();


//    std::cout << ctrl.getStateText() << std::endl;

    term::pause();

    return 0;
}
