#include <iostream>
#include <utility>
#include <cassert>

#include <cpe/core/terminal.h>
#include <cpe/ui/write/TextCanvas.h>
#include <cpe/ui/element/MessageBox.h>

#include "common.h"

using namespace cpe;

#undef MessageBox

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    MessageBox mb;
    mb.text("Это проверка вместимости текста в диалоговое 'окно' сообщения. Текст должен быть укомплектован и обрезан в случае необходимости."_dos);
    mb.border_style(DualBorder::TOP | DualBorder::RIGHT);
    mb.show({10, 100});

    std::string message = "Привет! Это проверка сраного канваса... Ой. Холста. "
                          "Нужно чтобы он не выходил за гребанные границы.\n"_dos;

    TextCanvas tc1({15, 15});
    tc1.cursor_style().foreground().set(Colors::LT_YELLOW);
    tc1.draw(message);
    tc1.output_to(std::cout);

    TextCanvas tc2({25, 25});
    tc2.cursor_style().foreground().set(Colors::LT_PURPLE);
    tc2.draw(std::string(25*25, 'X'));

    tc1.cursor_position({-5, -5});
    tc1.draw(tc2, true);
    tc1.output_to(std::cout);

    term::pause();

    return 0;
}
