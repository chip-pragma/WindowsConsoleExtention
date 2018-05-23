#include "Menu.h"

namespace cpe {

MenuData::~MenuData() { }

void MenuData::add_item(uint32_t itemId, const std::string &text) {
    mItems.insert_or_assign(itemId, text);
}

void MenuData::remove_item(uint32_t itemId) {
    mItems.erase(itemId);
}

Menu::~Menu() { }

void Menu::on_write(Buffer &buf) {

}
}