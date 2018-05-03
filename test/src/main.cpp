#include <iostream>
#include <string>

#include <cpe/core/terminal.h>

#include "common.h"
#include "controller/MainController.h"
#include "view/MainView.h"

using namespace cpe;

void testView() {
    MainView view;
    auto &ctrl = view.initialize();
    ctrl.setHintParam("Проверка ХинтПарама (аля 1С)"_dos);
    view.run();

    std::cout << "Введено: "_dos << ctrl.value() << std::endl;
}

void testBufferSize() {
    term::outputBufferSize(Point(150, 200));

    while (true) {
        auto p = term::outputBufferSize();
        std::cout << "X:" << p.x << " Y:" << p.y << std::endl;
        term::pause();
    }
}

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    testView();

    return 0;
}
