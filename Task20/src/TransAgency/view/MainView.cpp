#include "MainView.h"
#include "TransAgency/common.h"

void MainView::on_initialize() {
    auto &ncData = mnCaption.data();
    ncData.border().style().apply(cpe::BorderStyle::DB_ALL);
    ncData.text().push_back({"СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos, {cpe::Colors::LT_GREEN, std::nullopt}});
    ncData.text().push_back({"ТРАНСПОРТНОГО АГЕНСТВА"_dos, {cpe::Colors::LT_YELLOW, cpe::Colors::BLUE}});
    ncData.icon() = cpe::StyledChar('i', {cpe::Colors::LT_TEAL, std::nullopt});
    ncData.wait(true);
    add_element(mnCaption);
}
