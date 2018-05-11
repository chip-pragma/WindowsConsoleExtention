#include <iostream>
#include <utility>
#include <cpe/core/terminal.h>
#include <cpe/ui/write/TextCanvas.h>
#include <cpe/ui/element/reader/IValidator.h>
#include <cpe/ui/element/reader/IConverter.h>
#include <cpe/ui/element/reader/Reader.h>
#include <cpe/ui/element/MessageBox.h>
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

    TextCanvas tc(Point(7, 3));
    assert(tc.cursor_position() == Point());

    tc.cursor_position(Point(7, 1));
    std::cout << tc.cursor_position().to_string() << std::endl;
    assert(tc.cursor_position() == Point(0, 2));

    tc.cursor_position(Point(-7, -1));
    std::cout << tc.cursor_position().to_string() << std::endl;
    assert(tc.cursor_position() == Point(0, 2));

    term::pause();

    return 0;
}
