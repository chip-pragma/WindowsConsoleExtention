#include <iostream>
#include <utility>
#include <cassert>

#include <cpe/core/terminal.h>
#include <cpe/ui/reader/LineReader.h>
#include <cpe/third/json.hpp>
#include <cpe/ui/output/StyledText.h>
#include <cpe/ui/writer/Notification.h>

#include "common.h"

using namespace cpe;
using json = nlohmann::json;

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    Notification notif;
    StyledText st;
    st.push_back({"Проверка"_dos, {Colors::LT_YELLOW, Colors::RED}});
    st.push_back({" ", {Colors::BLACK, Colors::WHITE}});
    st.push_back({"стилизованного"_dos, {Colors::LT_GREEN, Colors::PURPLE}});
    st.push_back({" ", {Colors::BLACK, Colors::WHITE}});
    st.push_back({"текста"_dos, {Colors::LT_RED, Colors::BLUE}});
    notif.data().text() = st;
    notif.data().border().style().apply(BorderStyle::DB_BOTTOM | BorderStyle::DB_RIGHT);
    Buffer buf({50, 10});
    notif.write(buf);
    std::cout << buf;

    term::pause();

    return 0;
}
