#include <iostream>

#include "cpe/core/Encoding.h"
#include "cpe/core/Console.h"
#include "cpe/ui/LineReader.h"
#include "cpe/ui/IModel.h"
#include "cpe/ui/ConsoleApplication.h"

using namespace cpe::ui;
using namespace cpe::core;

namespace {

std::string encode(const std::string &src) {
    return encoding::decode(866, encoding::toWChar(65001, src));
}

}

int main() {
    console::setTitle(L"Текст консоли");

    console::setOutputCp(65001);
    console::setInputCp(1251);

    std::cout << "Кодировка вывода: " << console::getOutputCp() << "\n";
    std::cout << "Кодировка ввода: " << console::getInputCp() << std::endl;
    std::cout << "Кодировка окружения: " << setlocale(LC_ALL, "") << std::endl << std::endl;
    std::cout << "\u2566";



    // TODO проверка ui::View

    ConsoleApplication app;
    Scene main;

    app.run(main);

    console::pause();

    return 0;
}
