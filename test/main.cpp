#include <iostream>

#include "cpe/core/Encoding.h"
#include "cpe/core/Console.h"
#include "cpe/ui/LineReader.h"
#include "cpe/ui/IModel.h"
#include "cpe/ui/ConsoleApp.h"

using namespace cpe::ui;
using namespace cpe::core;

namespace {

std::string encode(const std::string &src) {
    return encoding::fromWideChar(866, encoding::toWideChar(65001, src));
}

}

int main() {
    console::setTitle(L"Текст консоли");

    std::cout << ::encode("Кодировка вывода: ") << console::getOutputCp() << "\n";
    std::cout << ::encode("Кодировка ввода: ") << console::getInputCp() << std::endl;
    std::cout << ::encode("\u255F");

    // TODO чтение с клавиатуры
    // TODO реализация MVC

    ConsoleApp app;
    Scene main;

    app.run(main);
    std::string line;

    std::getline(std::cin, line);

    console::pause();

    return 0;
}
