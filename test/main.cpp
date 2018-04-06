#include <iostream>
#include <string>
#include <conio.h>

#include "cpe/core/Platform.h"
#include "cpe/core/Encoding.h"
#include "cpe/core/Console.h"
#include "cpe/core/format/LineReader.h"

using namespace cpe::core;
using namespace cpe::core::format;

namespace {

std::string encode(const std::string &src) {
    return encoding::encode(866, encoding::decode(65001, src));
}

}


int main() {
    std::cout << "CP out: " << console::getOutputCp() << std::endl;
    std::cout << "CP in: " << console::getInputCp() << std::endl << std::endl;

    console::setTitle(encode("Текст консоли"));
    console::setInputCp(866);
    console::setOutputCp(866);

    if (!console::setBufferSize(Point(100, 150))) {
        std::cout << encode("Не удалость изменить размер буфера ") << GetLastError() << std::endl;
    }

    console::setForeColor(Color::LT_TEAL);
    std::string input;
    OutputFormat of;
    of.setTabLength(7);
    of.setUnfinished("~");
    LineReader rl;
    rl.read(input, of);

    // TODO добавить noexcept у функций CpeLib
    // TODO добавить свой класс CpeException

    console::setForeColor(Color::LT_RED);
    std::cout << input << std::endl;

    console::setForeColor(Color::LT_PURPLE);
    console::pause();

    return 0;
}
