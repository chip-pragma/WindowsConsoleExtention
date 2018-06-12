#include "MenuReader.h"

namespace cpe {

MenuReader::~MenuReader() { }

void MenuReader::setCommandItems(MenuItemVector &itemList) {
    mCommandItems.clear();
    mCommandItems.insert(mCommandItems.cbegin(), itemList.begin(), itemList.end());
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


