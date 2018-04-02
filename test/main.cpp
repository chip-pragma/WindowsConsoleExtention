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

    std::cout << encode("Приуэт! HALLO") << std::endl;

    std::string input;
    std::getline(std::cin, input);

    std::cout << input << std::endl;

    getch();

    return 0;
}
