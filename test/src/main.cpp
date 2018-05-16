#include <iostream>
#include <utility>
#include <cassert>

#include <cpe/core/terminal.h>
#include <cpe/ui/reader/LineReader.h>

#include "common.h"

using namespace cpe;

#undef MessageBox

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    // TODO комманды при работе ввода в ридерах
    // TODO Реализация MVC
    // TODO Каждому элементу/ридеру назначен свой Work'ер, который выполняется в View
    // TODO Выполнение View-элементов как Work (паттерн Command)


    //fixme Не нравится ссылка (???)
    LineReader reader;
    reader.add_command(1, "first");
    reader.add_command(2, "second");
    reader.add_command(3, "break");

    bool breaking = false;
    while (!breaking) {
        auto result = reader.read();
        if (result.type() == ReaderResultType::VALUE) {
            std::cout << "Введено значение: "_dos << "\n";
        } else if (result.type() == ReaderResultType::COMMAND) {
            std::cout << "Команда: "_dos;
            switch (result.command()) {
                case 1:
                    std::cout << "первача";
                    break;
                case 2:
                    std::cout << "вторяча";
                    break;
                case 3:
                    std::cout << "прерывание цикла";
                    breaking = true;
                    break;
                default:
                    std::cout << "[ИД НЕ ЗАДАН]";
                    break;
            }
            std::cout << "\n";
        }
    }

    term::pause();

    return 0;
}
