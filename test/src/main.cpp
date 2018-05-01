#include <iostream>
#include <cpe/core/terminal.h>

#include "common.h"
#include "controller/MainController.h"
#include "view/MainView.h"

using namespace cpe;

namespace {

// TODO Реализовать Property с возможностью задавать nullptr
// TODO Переработать Property

}

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    MainController ctrl;
    MainView(ctrl).run();

    std::cout << "Введено: "_dos << ctrl.testProperty() << std::endl;

    term::pause();

    return 0;
}
