#include <iostream>

#include <cpe/core/terminal.h>

#include "controller/MainController.h"
#include "view/MainView.h"

using namespace cpe;

void testView() {
    std::cout << "[View test]\n" << std::endl;

    auto bufSize = term::windowSize();
    std::cout << "X:" << bufSize.x << " Y:" << bufSize.y << std::endl;

    MainView view;
    auto &ctrl = view.initialize();
    ctrl.setHintParam("Проверка ХинтПарама (аля 1С)"_dos);
    view.run();

    std::cout << "Введено: "_dos << ctrl.value() << std::endl;
}

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    testView();

    term::pause();

    return 0;
}
