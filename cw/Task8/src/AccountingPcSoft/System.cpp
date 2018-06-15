#include "System.h"
#include "Item.h"

#include <fstream>
#include <algorithm>

namespace cw {

System::~System() {
    // Очистка памяти от инвентаря
    for (auto i = _items.begin();
         i != _items.end();
         i++) {
        delete (*i);
    }
}


void System::loadFrom(std::string file) {
    std::ifstream fs(file);
    if (!fs.is_open())
        throw std::string("Файл системы не был открыт!");

    // Чтение
    while (!fs.eof()) {
        auto item = new Item();
        std::getline(fs, item->_name);
        std::getline(fs, item->_description);
        std::getline(fs, item->_buildNumber);
        std::getline(fs, item->_itemNumber);
        this->_items.push_back(item);
    }

    fs.close();
}

void System::saveTo(std::string file) const {
    std::ofstream fs(file);
    if (!fs.is_open())
        throw std::string("Файл системы не был открыт!");

    // Чтение
    bool first = true;
    for (auto i = _items.cbegin();
         i != _items.cend();
         i++) {
        Item *item = (*i);
        if (!first)
            fs << std::endl;

        fs << item->_name;
        fs << std::endl << item->_description;
        fs << std::endl << item->_buildNumber;
        fs << std::endl << item->_itemNumber;
        first = false;
    }

    fs.close();
}

void System::addItem(std::string name, std::string desc, std::string buildNum, std::string itemNum) {
    // Удаление пробелов
    name = trim(name);
    desc = trim(desc);
    buildNum = trim(buildNum);
    itemNum = trim(itemNum);

    // Создание
    auto item = new Item();
    item->_name = name;
    item->_description = desc;
    item->_buildNumber = buildNum;
    item->_itemNumber = itemNum;

    // Проверка на совпадение
    for (auto i = _items.begin();
         i != _items.end();
         i++) {
        Item *iItem = (*i);
        if (iItem->_buildNumber == buildNum) {
            delete item;
            throw std::string("Инвертарь с указанным заводским номером уже зарегестрирован в системе!");
        }
        if (iItem->_itemNumber == itemNum) {
            delete item;
            throw std::string("Инвертарь с указанным заводским номером уже зарегестрирован в системе!");
        }
    }

    _items.push_back(item);
}

void System::editItem(Item *item, std::string name, std::string desc, std::string buildNum, std::string itemNum) {
    // Удаление пробелов
    name = trim(name);
    desc = trim(desc);
    buildNum = trim(buildNum);
    itemNum = trim(itemNum);

    // Пустые строки
    if (name.empty()) name = item->_name;
    if (desc.empty()) desc = item->_description;
    if (buildNum.empty()) buildNum = item->_buildNumber;
    if (itemNum.empty()) itemNum = item->_itemNumber;

    // Изменение
    item->_name = name;
    item->_description = desc;
    item->_buildNumber = buildNum;
    item->_itemNumber = itemNum;
}

void System::removeItem(Item *item) {
    _items.erase(std::find(_items.begin(), _items.end(), item));
}

std::vector<Item *> System::getSortItems(SortItemBy sortMode) const {
    std::vector<Item *> sorted = _items;

    if (sortMode == SortItemBy::CW_SORTBY_NAME) {
        std::sort(
            sorted.begin(),
            sorted.end(),
            [](Item *i1, Item *i2) {
                return (i1->getName().compare(i2->getName()) < 0);
            });
    } else if (sortMode == SortItemBy::CW_SORTBY_BUILD) {
        std::sort(
            sorted.begin(),
            sorted.end(),
            [](Item *i1, Item *i2) {
                return (i1->getBuildNumber().compare(i2->getBuildNumber()) < 0);
            });
    } else if (sortMode == SortItemBy::CW_SORTBY_ITEM) {
        std::sort(
            sorted.begin(),
            sorted.end(),
            [](Item *i1, Item *i2) {
                return (i1->getItemNumber().compare(i2->getItemNumber()) < 0);
            });
    }

    return sorted;
}

std::vector<Item *> System::findItems(std::string sub, int findFlags) const {
    std::vector<Item *> finded;

    for (auto i = _items.begin();
         i != _items.end();
         i++) {
        Item *item = (*i);

        if ((findFlags & cw::FindItemBy::CW_FINDBY_NAME) != 0 &&
            (item->_name.find(sub, 0) != std::string::npos)) {
            finded.push_back(item);
            continue;
        }
        if ((findFlags & cw::FindItemBy::CW_FINDBY_DESCRIPTION) != 0 &&
            (item->_description.find(sub, 0) != std::string::npos)) {
            finded.push_back(item);
            continue;
        }
        if ((findFlags & cw::FindItemBy::CW_FINDBY_BUILD) != 0 &&
            (item->_buildNumber.find(sub, 0) != std::string::npos)) {
            finded.push_back(item);
            continue;
        }
        if ((findFlags & cw::FindItemBy::CW_FINDBY_ITEM) != 0 &&
            (item->_itemNumber.find(sub, 0) != std::string::npos)) {
            finded.push_back(item);
            continue;
        }
    }

    return finded;
}

std::string System::trim(std::string src) {
    int i = 0;
    for (; i < src.size(); i++)
        if (src[i] != ' ') break;
    int j = src.size() - 1;
    for (; j >= 0; j--)
        if (src[j] != ' ') break;

    return src.substr(i, j - i + 1);
}

}