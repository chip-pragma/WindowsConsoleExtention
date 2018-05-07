#include <iostream>

#include <cpe/core/terminal.h>
#include <cpe/ui/print/TextCanvas.h>

#include "controller/MainController.h"
#include "view/MainView.h"

using namespace cpe;

// TODO Реализация комманд при выполнении элементов в представлении
// TODO Продумать вывод сообщения о не правильном вводе в ридерах (возможно отдельным классом диалогового сообщения)

void testView() {
    std::cout << "[View test]\n" << std::endl;

    auto bufSize = term::windowSize();
    std::cout << "X:" << bufSize.x << " Y:" << bufSize.y << std::endl;

    MainView view;
    auto &ctrl = view.initialize();
    ctrl.setHintParam("Проверка ХинтПарама (аля 1С)"_dos);
    view.run(true, false);

    std::cout << "Введено: "_dos << ctrl.value() << std::endl;
}

void testCanvas() {
    cpe::TextFormat tf;
    tf.setTabLength(5);
    tf.setUnfinished("<~>");

    cpe::TextCanvas tc(Point(20,10));
    tc.cursorStyle().foreground().set(cpe::Colors::LT_PURPLE);
    tc.cursorStyle().background().set(cpe::Colors::BLUE);
    tc.setFormat(tf);
    tc << "j\n\to\n\t\tp\n\n\t\t\t\tA\nfirst\t\n\t\t";
    tc.cursorStyle().foreground().set(cpe::Colors::LT_YELLOW);
    tc.cursorStyle().background().set(cpe::Colors::GREEN);
    tc << "second\t\tthird\t\n\tfourth\t\tfiveth\t\tsixth EPTA";
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
