#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

#include "System.h"
#include "Item.h"

// Перегрузка оператора вывода в поток 
// для корректного отображения кириллицы
std::string cyr(std::string str) {
    char dest[1024];
    CharToOemBuffA(str.c_str(), dest, 256);
    return std::string(dest);
}

// Консольный интерфейс пользователя
namespace ui {

// Главное меню
bool mainMenu();

// Вывод списка инвентаря
void writeItemList(std::vector<cw::Item *> vec);

// Ввод инфо о инвентаре
void readItemData(std::string &name, std::string &desc, std::string &buildNum, std::string &itemNum);

}

// Глобальные переменные
namespace global {

// Система 
auto system = new cw::System();
// Режим сортировки
cw::SortItemBy sortMode = cw::SortItemBy::CW_SORTBY_NONE;
// Последний полученный список инвентаря
std::vector<cw::Item *> curItems;
// Имя файла данных 
std::string dataFile = "cw_data.aps";

cw::Item *getItemByIndex(int index) {
    if (index < 0 || index >= curItems.size())
        throw std::string("Некорректный индекс");

    return curItems[index];
}

}


// Главная точка входа в программу
int main() {
    system("title Автоматизация учета инвентаря");

    // Чтение данных
    try {
        global::system->loadFrom(global::dataFile);

    }
    catch (std::string &e) {
        std::cout << cyr("[!] Файл данных не найден. При завершении программы будет создан новый.\n\n");
        system("pause");
    }

    // Цикл программы
    while (ui::mainMenu()) {
    };

    system("pause");
    return 0;
}

bool ui::mainMenu() {
    system("cls");

    // Список инвентаря
    global::curItems = global::system->getSortItems(global::sortMode);
    ui::writeItemList(global::curItems);
    std::cout << std::string(79, '=') << std::endl;

    // Меню
    std::cout << cyr("\nВыберите действие:") << std::endl;
    std::cout << cyr("  1. Добавить инвентарь (ПК или ПО)") << std::endl;
    std::cout << cyr("  2. Изменить инвентарь") << std::endl;
    std::cout << cyr("  3. Удалить инвентарь") << std::endl;
    std::cout << cyr("  |") << std::endl;
    std::cout << cyr("  4. Сортировка") << std::endl;
    std::cout << cyr("  5. Поиск") << std::endl;
    std::cout << cyr("  6. Сброс (вывод исходного списка)") << std::endl;
    std::cout << cyr("  |") << std::endl;
    std::cout << cyr("  0. Сохранить изменения и завершить работу") << std::endl;

    // Ввод пункта меню
    std::cout << cyr("\nВведите номер действия: ") << std::endl;
    int mi = -1;
    std::cin >> mi;

    if (mi == 0) {
        global::system->saveTo(global::dataFile);
        system("cls");
        std::cout << cyr("Программа завершена\n") << std::endl;
        return false;
    } else if (mi == 1) {
        system("cls");

        std::string itemName;
        std::string itemDesc;
        std::string itemBuild;
        std::string itemItem;

        ui::readItemData(itemName, itemDesc, itemBuild, itemItem);

        try {
            global::system->addItem(itemName, itemDesc, itemBuild, itemItem);
        }
        catch (std::string &e) {
            system("cls");
            std::cout << e << "\n\n";
            system("pause");
        }
    } else if (mi == 2) {
        int index = 0;
        std::cout << cyr("Индекс: ");
        std::cin >> index;
        cw::Item *item = nullptr;

        try {
            item = global::getItemByIndex(index);
        }
        catch (std::string &e) {
            system("cls");
            std::cout << cyr(e) << std::endl;
            system("pause");
            return true;
        }

        system("cls");
        std::string itemName;
        std::string itemDesc;
        std::string itemBuild;
        std::string itemItem;

        ui::readItemData(itemName, itemDesc, itemBuild, itemItem);

        try {
            global::system->editItem(item, itemName, itemDesc, itemBuild, itemItem);
        }
        catch (std::string &e) {
            system("cls");
            std::cout << e << "\n\n";
            system("pause");
        }
    } else if (mi == 3) {
        int index = 0;
        std::cout << cyr("Индекс: ");
        std::cin >> index;
        cw::Item *item = nullptr;

        try {
            item = global::getItemByIndex(index);
        }
        catch (std::string &e) {
            system("cls");
            std::cout << cyr(e) << std::endl;
            system("pause");
            return true;
        }

        global::system->removeItem(item);
    } else if (mi == 4) {
        int mode = 0;
        std::cout << cyr("Выберите режим сортировки (1 - имя, 2 - завод. ном., 3 - инвент. ном.): \n");
        std::cin >> mode;

        if (mode < 1 || mode > 3) {
            system("cls");
            std::cout << cyr("Неверный номер режима сортировки!") << "\n\n";
            system("pause");
            return true;
        }

        global::sortMode = (cw::SortItemBy) mode;
    } else if (mi == 5) {
        std::cout << cyr("Введите искомую подстроку: \n");
        std::cin.ignore();
        std::string sub;
        std::getline(std::cin, sub);

        std::cout << cyr("Введите флаги поиска в формате [1234]: \n");
        std::cout << cyr("  1 - по имени \n");
        std::cout << cyr("  2 - по описанию \n");
        std::cout << cyr("  3 - по завод. ном. \n");
        std::cout << cyr("  4 - по инверт. ном. \n");
        std::cout << cyr("(Пример: 1011 - по имени, по завод. ном. и по инверт. ном.)\n");
        std::cout << cyr("(Пример: 0110 - по описанию и по завод. ном.)\n");
        std::cout << cyr("(Пример: 0100 - по описанию)\n");
        std::cout << cyr("Флаг поиска: \n");
        std::cin.ignore();
        std::string flag;
        std::getline(std::cin, flag);

        int intFlag = 0;
        for (int i = 0; i < 4 && i < flag.size(); i++) {
            if (flag[i] != '0')
                intFlag |= (1 << i);
        }

        // Вывод
        std::cout << cyr("[Поиск завершен]\n\n");
        system("cls");
        ui::writeItemList(global::system->findItems(sub, intFlag));
        system("pause");

    } else if (mi == 6) {
        global::sortMode = cw::CW_SORTBY_NONE;
    } else {
        system("cls");
        std::cout << cyr("\n\nНеверный пункт меню!") << std::endl;
        system("pause");
    }

    return true;
}

void ui::writeItemList(std::vector<cw::Item *> vec) {
    // Отступы
    int wIndex = 3;
    int wName = 40;
    int wDesc = 35;
    int wBuild = 40;
    int wItem = 35;

    // Вывод
    for (auto i = vec.begin();
         i != vec.end();
         i++) {
        cw::Item *item = (*i);
        int index = std::distance(vec.begin(), i);

        std::cout << std::setw(wIndex) << std::left << index;
        std::cout << std::setw(wName) << std::left << item->getName().substr(0, wName - 1);
        std::cout << std::setw(wDesc) << std::left << item->getDescription().substr(0, wDesc - 1);
        std::cout << std::endl << std::string(wIndex, ' ');
        std::cout << std::setw(wBuild) << std::left << item->getBuildNumber().substr(0, wBuild - 1);
        std::cout << std::setw(wItem) << std::left << item->getItemNumber().substr(0, wItem - 1);
        std::cout << std::endl;
    }
}

void ui::readItemData(std::string &name, std::string &desc, std::string &buildNum, std::string &itemNum) {
    std::cout << cyr("[Введите данные инвентаря]\n") << std::endl;
    std::cin.ignore();
    std::cout << cyr("Наименование:   ") << std::endl;
    std::getline(std::cin, name);
    std::cout << cyr("Описание:       ") << std::endl;
    std::getline(std::cin, desc);
    std::cout << cyr("Заводской ном.: ") << std::endl;
    std::getline(std::cin, buildNum);
    std::cout << cyr("Инвентар. ном.: ") << std::endl;
    std::getline(std::cin, itemNum);
};
