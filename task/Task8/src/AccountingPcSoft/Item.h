#pragma once

#include <string>

namespace cw {

// Предопределение 
class System;

// ПК и ПО для учета (инвентарь)
class Item {
    // Дружественный класс для доступа к закрытым членам
    friend class System;

public:
    // Наименование ПК или ПО
    std::string getName() const;

    // Описание
    std::string getDescription() const;

    // Заводской номер
    std::string getBuildNumber() const;

    // Инвентарный номер
    std::string getItemNumber() const;

private:
    // Наименование ПК или ПО
    std::string _name;
    // Описание
    std::string _description;
    // Заводской номер
    std::string _buildNumber;
    // Инвентарный номер
    std::string _itemNumber;
};

}