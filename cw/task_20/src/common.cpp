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

wce::Notification infoNotification() {
    Notification e;
    e.border.style.apply(BorderStyle::DB_BOTTOM);

    e.icon = StyledChar('i', {console::C_LT_TEAL, std::nullopt});
    
    return Notification();
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
