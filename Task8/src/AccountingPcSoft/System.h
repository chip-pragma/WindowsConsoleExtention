#pragma once

#include <string>
#include <vector>

namespace cw {

// Предопределение 
class Item;

// Режим сортировки
enum SortItemBy {
    // Не сортировать
        CW_SORTBY_NONE,
    // По наименованию
        CW_SORTBY_NAME,
    // По заводскому номеру
        CW_SORTBY_BUILD,
    // По инвентарному номеру
        CW_SORTBY_ITEM,
};
// Режим поиска (флаги)
enum FindItemBy {
    CW_FINDBY_NAME = 1,
    CW_FINDBY_DESCRIPTION = 2,
    CW_FINDBY_BUILD = 4,
    CW_FINDBY_ITEM = 8,
};

// Система автоматизированного учета
class System {
public:
    ~System();

    // Загрузка из файла
    void loadFrom(std::string file);

    // Сохранение в файл
    void saveTo(std::string file) const;

    // Добавить новый инвентарь
    void addItem(std::string name, std::string desc, std::string buildNum, std::string itemNum);

    // Изменить сущ. инвентарь
    void editItem(Item *src, std::string name, std::string desc, std::string buildNum, std::string itemNum);

    // Удалить инвентарь
    void removeItem(Item *src);

    // Получить сортированный инвентарь
    std::vector<Item *> getSortItems(SortItemBy sortMode) const;

    // Поиск инвентаря по указанным полям
    std::vector<Item *> findItems(std::string sub, int findFlags) const;

    // Очистка строки от начальных и конечных пробелов
    static std::string trim(std::string src);

private:
    // Зарегистрированный инвентарь
    std::vector<Item *> _items;
};

}