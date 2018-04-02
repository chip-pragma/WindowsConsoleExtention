#include <iostream>
#include <string>
#include <conio.h>

#include "cpe/Core.h"

using namespace cpe::core;

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

    for (uint16_t i = 0; i < 16; i++) {
        console::setForeColor(platform::toCpeColor(i));
        std::cout << encode("ИСХОДНЫЙ ");
        console::setBackColor(platform::toCpeColor(i));
        std::cout << "        ";

        auto fore = console::getForeColor();
        console::setForeColor(fore);
        std::cout << encode("ВОССТАНОВЛЕННЫЙ ");
        auto back = console::getBackColor();
        console::setBackColor(back);
        std::cout << "               ";

        std::cout << std::endl;
    }

    std::string input;
    std::getline(std::cin, input);

    std::cout << input << std::endl;

    console::pause();

    return 0;
}
