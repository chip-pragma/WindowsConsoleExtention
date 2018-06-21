#include "common.h"

using namespace wce;

namespace {

Encoder encUtf8(Encoder::UTF8); // NOLINT
Encoder encCp866(Encoder::CP866); // NOLINT

}

namespace templates {

void initialize() {
    console::resetColorTable();
    console::setBackground(console::C_BLACK);
    console::setForeground(console::C_WHITE);
    BorderStyle::finalEncoding = Encoder(Encoder::CP866);
}

wce::Label wrapLabel(uint32_t wrapCount) {
    Label e;
    e.text = StyledText().append(std::string(wrapCount, '\n'));
    return e;
}

wce::Notification infoNotification() {
    Notification e;
    e.border.style.apply(BorderStyle::DB_BOTTOM);
    e.border.color.foreground = console::C_DK_TEAL;
    e.icon = StyledChar('i', {console::C_LT_TEAL, std::nullopt});
    return e;
}

wce::Menu simpleMenu() {
    Menu e;
    e.commandColor.foreground = console::C_LT_PURPLE;
    e.caption
        .setFore(console::C_DK_YELLOW)
        .append("Доступные действия"_dos);
    e.readerHint
        .setFore(console::C_DK_YELLOW)
        .append("Выберите действие"_dos);
    auto &eb = e.border;
    eb.style.apply(BorderStyle::DB_OUT_V);
    eb.color.foreground = console::C_DK_YELLOW;
}

wce::MenuReader simpleMenuReader() {
    MenuReader e;
    e.color.foreground = console::C_LT_PURPLE;
    e.errorText = "Действие не определено. Введите комманду (одну из комманд), представленную перед наименованием действия."_dos;
    return e;
}

}


/**
 * Кодирует строку из UTF8 в CP866
 */
std::string operator "" _dos(const char *src, size_t size) {
    return encCp866.to(encUtf8.from(src));
}

std::string fromUtf8ToDos866(const std::string &src) {
    return encCp866.to(encUtf8.from(src));
}
