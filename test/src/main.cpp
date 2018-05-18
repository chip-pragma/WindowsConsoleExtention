#include <iostream>
#include <utility>
#include <cassert>

#include <cpe/core/terminal.h>
#include <cpe/ui/reader/LineReader.h>

#include "common.h"
#include "TestView.h"

using namespace cpe;

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    // TODO комманды при работе ввода в ридерах
    // TODO Реализация MVC (см. Mvc.puml)
    // TODO Выполнение View-элементов c помощью ElementItem оберток
    // TODO Ридеры как наследникики WriterBase

    /*LineReader reader;
    reader.add_command("first");
    reader.add_command("second");
    reader.add_command("break");

    bool breaking = false;
    while (!breaking) {
        auto result = reader.read();
        if (result.type() == ResultReadType::VALUE) {
            std::cout << "Введено значение: "_dos << result.value() << "\n";
        } else if (result.type() == ResultReadType::COMMAND) {
            std::cout << "Команда: "_dos;
            if (result.command() == "first")
                std::cout << "первача";
            else if (result.command() == "second")
                std::cout << "вторяча";
            else if (result.command() == "break") {
                std::cout << "прерывание цикла";
                breaking = true;
            } else {
                std::cout << "[неизвестная команда]";
            }

            std::cout << "\n";
        }
    }*/

    TestView view;
    auto ctrl = view.initialize();
    ctrl.test_func();
    view.show(false, true);

    term::pause();

    return 0;
}
