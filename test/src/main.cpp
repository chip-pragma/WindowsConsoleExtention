#include <iostream>
#include <utility>
#include <cpe/core/terminal.h>
#include <cpe/ui/write/TextCanvas.h>
#include <cassert>

#include "common.h"

using namespace cpe;

#undef MessageBox

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

//    MessageBox mb;
//    mb.text("Это проверка вместимости текста в диалоговое 'окно' сообщения. Текст должен быть укомплектован и обрезан в случае необходимости."_dos);
//    mb.border_style(DualBorder::OUT_V);
//    mb.show(Point(30,5));

    std::string message = "Привет! Это проверка сраного канваса... Ой. Холста. "
                          "Нужно чтобы он не выходил за гребанные границы."_dos;
    Size beginSize = Size(15, 5);

    for (int i = 0; i <= 10; i++) {
        auto s = Size(beginSize.width() - i, beginSize.height() + i);
        TextCanvas tc(s);
        tc.draw(message);
        tc.output_to(std::cout << "\n[" << i << ":" << s.height() * s.width() << "]\n");
    }

//    TextCanvas tc(Size(10, 10));
//    tc.cursor_style().foreground().set(Colors::LT_RED);
//    tc.draw(message);
//    tc.output_to(std::cout);

    term::pause();

    return 0;
}
