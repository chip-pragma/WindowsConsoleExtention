#include <iostream>

#include <cpe/core/terminal.h>
#include <cpe/ui/TextCanvas.h>

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

void testCanvas() {
    cpe::TextFormat tf;
    tf.setTabLength(2);

    cpe::TextCanvas tc(50, 10);
    tc.setPen(cpe::Colors::LT_PURPLE);
    tc.setBrush(cpe::Colors::BLUE);
    tc.setFormat(tf);
    tc << "j\n\to\n\t\tp\n\n\t\t\t\tA\nfirst\t\n\t\tsecond\t\tthird\t\n\tfourth\t\tfiveth\t\tsixth EPTA";
    std::cout << tc
              << " AW:" << tc.getActualSize().x
              << " AH:" << tc.getActualSize().y
              << std::endl;
}

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    testCanvas();

    term::pause();

    return 0;
}
