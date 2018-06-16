#include "MenuReader.h"

namespace wce {

MenuReader::~MenuReader() { }

void MenuReader::setCommandItems(MenuItemSet &itemList) {
//    m_commandItems.clear();
//    m_commandItems.insert(itemList.begin(), itemList.end());
    m_commandItems = itemList;
}

bool MenuReader::onConvert(std::string &srcLine, uint32_t &convertedValue) {
    for (const auto &item : m_commandItems) {
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


