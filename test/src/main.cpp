#include <iostream>
#include <utility>
#include <cassert>

#include <cpe/core/terminal.h>
#include <cpe/ui/write/Buffer.h>
#include <cpe/ui/element/MessageBox.h>

#include "common.h"

using namespace cpe;

#undef MessageBox

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    std::string message = "Привет! Это проверка сраного канваса... Ой. Холста. "
                          "Нужно чтобы он не выходил за гребанные границы.\n"_dos;

    Buffer tc1({20, 20});
    tc1.draw({message, {Colors::LT_YELLOW, nullptr}});
    tc1.output_to(std::cout);

    MessageBox mb;
    mb.message().text("Это проверка вместимости текста в диалоговое 'окно' сообщения. "
                      "Текст должен быть укомплектован и обрезан в случае необходимости."_dos);
    mb.border().border().apply(Border::DB_TOP | Border::DB_RIGHT);
    mb.border().color().foreground().set(Colors::LT_TEAL);
    mb.caption().set({"Заголовок супер сообщения"_dos, {Colors::RED, Colors::BLUE}});
//    mb.icon().set({'&', {Colors::LT_RED, Colors::GREEN}});

    auto tc3 = tc1.extract({2, 2}, {10, 10});
    mb.draw(tc3);
    tc1.output_to(std::cout);

    Buffer tc2({25, 25});
    tc2.draw({std::string(25 * 25, 'X'), {Colors::LT_PURPLE, nullptr}});

    tc1.cursor_position({-5, -5});
    tc1.draw(tc2, true);
    tc1.output_to(std::cout);

    term::pause();

    return 0;
}
