#include "MenuReader.h"

namespace wce {

MenuReader::~MenuReader() { }

void MenuReader::setCommandItems(MenuItemSet &itemList) {
//    mCommandItems.clear();
//    mCommandItems.insert(itemList.begin(), itemList.end());
    mCommandItems = itemList;
}

bool MenuReader::onConvert(std::string &srcLine, uint32_t &convertedValue) {
    for (const auto& item : mCommandItems) {
        for (const auto& com : item.second->getCommandList()) {
            if (com == srcLine) {
                convertedValue = item.first;
                return true;
            }
        }
    }
    return false;
}

}


