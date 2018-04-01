#include "Console.h"
#include "utils/Text.h"
#include "ui/Menu.h"
#include "ui/Table.h"

#include <iostream>
#include <map>
#include <utility>

#include <ctime>
#include <cmath>

namespace _old {

Console::Console() :
        _foreColor(Color::WHITE),
        _defaultForeColor(Color::WHITE),
        _unfinished("..."),
        _tabSize(4),
        _debug(false) {
}

Console::~Console()
= default;


void Console::write(std::string str) {
    _addLastCurPos();

    std::string out;
    auto curPos = _getCursorPosition();
    for (char i : str) {
        if (i == '\t') {
            // Расстояние до след. таба
            auto nextTab = _tabSize - ((curPos.X + out.size()) % _tabSize);
            // ЕСЛИ расстояние не превышает ширину
            out += std::string(nextTab, ' ');
        } else
            out += str[i];
    }

    std::cout << _encode(out);
}

void Console::writeLine(std::string str, int nls) {
    write(std::move(str));
    writeLine(nls);
}

void Console::writeLine(int nls) {
    for (int i = 0; i < nls; i++)
        std::cout << std::endl;
}

bool Console::readLine(std::string *inValue, bool required) {
    _addLastCurPos();

    // Ввод
    std::string line;
    std::getline(std::cin, line);
    Text::trim(&line);

    // Правка
    if (!line.empty() || required) {
        *inValue = _decode(line);
        return true;
    }
    return false;
}

bool Console::readInt(int *inValue, std::string error, bool required) {
    auto lastPos = _getCursorPosition();

    int iNum = 0;
    while (true) {
        // Ввод
        std::string sNum;
        readLine(&sNum, required);
        tools::trim(&sNum);

        // ЕСЛИ пустая (оставить без изменений)
        if (sNum.empty() && !required)
            return false;

        // ЕСЛИ удалось преобразовать
        if (tools::string_to_int(sNum, &iNum))
            break;

        // Ошибка
        if (error.empty()) {
            clear(1);
            continue;
        }
        notification(error, Color::COLOR_RED);
        pause();
        clear(2);
        continue;
    }

    // Возврат
    *inValue = iNum;
    return true;
}

bool Console::readIntRange(int *inValue, int min, int max, std::string error, bool required) {
    // Проверка минмакса
    if (min > max) {
        int swaper = min;
        min = max;
        max = swaper;
    }
    // Ввод
    int value = *inValue;
    while (true) {
        if (!readInt(&value, error, required))
            return false;
        if (value < min || value > max) {
            if (error.empty()) {
                clear(1);
                continue;
            }
            notification(error, Color::COLOR_RED);
            pause();
            clear(2);
            continue;
        }
        break;
    }

    // Возврат
    *inValue = value;
    return true;
}

bool Console::readTime(time_t *inTime, bool seconds, std::string error, bool required) {
    time_t time;
    while (true) {
        std::string strTime;
        if (!readLine(&strTime, required) && !required)
            return false;

        if (cpe::tools::string_to_time(strTime, seconds, &time))
            break;
        else {
            if (error.empty()) {
                clear(1);
                continue;
            }
            notification(error, Color::COLOR_RED);
            pause();
            clear(2);
        }
    }

    // Возврат
    *inTime = time;
    return true;
}

bool Console::readDate(time_t *inDate, std::string error, bool required) {
    time_t date;
    while (true) {
        std::string strTime;
        if (!readLine(&strTime, required) && !required)
            return false;

        if (cpe::tools::string_to_date(strTime, &date))
            break;
        else {
            if (error.empty()) {
                clear(1);
                continue;
            }
            notification(error, Color::COLOR_RED);
            pause();
            clear(2);
        }
    }

    // Возврат
    *inDate = date;
    return true;
}


int Console::messageBox(std::string message,
                        std::string caption,
                        char iconSym,
                        std::string menuItems,
                        const Color& captionColor,
                        const Color& iconColor,
                        const Color& sideColor,
                        int dSide,
                        bool padding) {
    _addLastCurPos();

    // Подготовка
    Color previousColor = getForeColor();
    tools::trim(&caption);
    tools::trim(&message);
    tools::trim(&menuItems);
    auto b = tools::define_side_symbols(dSide);
    int maxWidth = 74;    // Макс. ширина бокса сообщения
    bool messageEmpty = message.empty();

    // Варианты ответа на сообщение
    std::vector<std::string> items;
    tools::split(menuItems, &items, "|");
    COORD choicePos = COORD();

    if (items.size() > 0) {
        message += "\n\nВарианты:\n";
        for (int i = 0; i < items.size(); i++) {
            tools::trim(&(items[i]));
            message += "  " + std::to_string(i + 1) + " - " + items[i] + "\n";
        }
        message += "Выбор: ";
    }

    // Ограничение области сообщения
    int widthMessage;
    auto linesMessage = layout(message, maxWidth - 4, &widthMessage);

    // Вывод
    int topWidth = widthMessage;

    // Начало
    setForeColor(sideColor);
    std::wcout << std::endl << " " << b["LT"] << b["T"];
    topWidth -= 1;
    // Иконка
    if (iconSym != 0) {
        std::cout << "[";
        setForeColor(iconColor);
        std::cout << iconSym;
        setForeColor(sideColor);
        std::wcout << "]" << b["T"];
        topWidth -= 4;
    }
    // Заголовок
    if (!caption.empty()) {
        std::cout << "[ ";

        setForeColor(captionColor);
        int widthCaption;
        auto linesCaption = layout(caption, topWidth - 5, &widthCaption, 1);
        std::cout << _encode(linesCaption[0]);

        setForeColor(sideColor);
        std::wcout << " ]";
        topWidth -= (widthCaption + 4);
    }
    // Верх рамки
    std::wcout << std::wstring(std::max(topWidth, 1) + 2, b["T"][0]) << b["RT"] << std::endl;
    // Отступы
    if (padding) {
        // Вставка отступа в конце
        linesMessage.push_back(" ");
        // ЕСЛИ сообщения нет, то удаление части
        if (!messageEmpty)
            linesMessage.insert(linesMessage.begin(), " ");
        else
            linesMessage.erase(linesMessage.begin());
    }
    // Минимальная ширина
    if (topWidth < 0) widthMessage += (-topWidth + 1);
    // Сообщение
    for (auto i = linesMessage.begin();
         i != linesMessage.end();
         i++) {
        std::wcout << " " << b["L"] << " ";
        setForeColor(previousColor);
        std::cout << _encode(*i);
        // Проверка предпоследней строки ("Выбор:", след. " (пустая строка)")
        if (items.size() > 0 && i == linesMessage.end() - 2)
            choicePos = _getCursorPosition();

        setForeColor(sideColor);
        std::wcout << std::wstring(widthMessage - i->size() + 1, ' ') << b["R"] << std::endl;
    }
// Нижняя часть
    setForeColor(sideColor);
    std::wcout << " " << b["LB"] << std::wstring(widthMessage + 2, b["B"][0]) << b["RB"] << "\n" << std::endl;

    // Ввод значения выбора
    int itemNum = -1;
    if (items.size() > 0) {
        setForeColor(previousColor);
        // Переход на позицию ввода
        auto curPos = _getCursorPosition();
        _setCursorPosition(choicePos);
        // Ввод пункта
        readIntRange(&itemNum, 1, items.size(), "", true);
        // Возврат
        _setCursorPosition(curPos);
        _lastCursorPositions.pop_back();
    }

    // Возврат
    setForeColor(previousColor);
    return itemNum;
}

void Console::notification(std::string message,
                           Color sideColor,
                           int dSide) {
    messageBox(
            message,
            "",
            0,
            "",
            Color::COLOR_WHITE,
            Color::COLOR_WHITE,
            sideColor,
            dSide,
            false);
}

void Console::writeMenu(Menu *const menu) {
    // Подготовка
    auto side = tools::define_side_symbols(cpe::DSIDE_ALL);
    Color previousColor = getForeColor();

    // Ограничение
    int widthCaption;
    auto linesCaption = layout(menu->_caption, 70, &widthCaption, 1);

    // Заголовок
    std::wcout << std::endl;
    setForeColor(menu->_sideColor);
    std::wcout << L" " << side["LT"] << side["T"] << L" ";
    setForeColor(menu->_captionColor);
    std::cout << _encode(linesCaption[0]) << std::endl;

    // Пустое пространство
    setForeColor(menu->_sideColor);
    std::wcout << " " << side["L"] << std::endl;

    // Пункты меню
    int nNormItems = 0;                // Неспециальных пунктов меню
    int itemIndent = 2;                // Отступ пунктов меню
    for (auto it = menu->_items.begin();
         it != menu->_items.end();
         it++) {
        // Пункт
        auto item = it->second;
        // ЕСЛИ специальный пункт меню
        if (item->isSpecial) {
            // Разделитель
            if (item->text == "separator") {
                setForeColor(menu->_sideColor);
                std::wcout << " " << side["L"] << std::endl;
            }
        } else {
            nNormItems++;
            // Рамка
            setForeColor(menu->_sideColor);
            std::wcout << L" \xC7" << std::wstring(itemIndent, L'\xC4') << L"[";
            // Индекс
            int index = item->index;
            if (index == menu->_nNospec && menu->_usingLast)
                index = 0;

            // Разметка текста
            int widthText;
            auto linesText = layout(item->text, 70 - itemIndent, &widthText);
            // первая строка с индексом (если много строк при разметке)
            setForeColor(item->foreColor);
            std::string forPadding = std::to_string(index);
            std::cout << forPadding;
            setForeColor(menu->_sideColor);
            std::wcout << L"] ";
            setForeColor(item->foreColor);
            std::cout << _encode(linesText[0]) << std::endl;
            // Последующие строки (если есть)
            for (int i = 1; i < linesText.size(); i++) {
                setForeColor(menu->_sideColor);
                std::wcout << L" " << side["L"];
                std::wcout << std::wstring(itemIndent + forPadding.size() + 3 /*две скобки и пробел*/, L' ');
                setForeColor(item->foreColor);
                std::cout << _encode(linesText[i]) << std::endl;
            }
        }
    }

    // Пустое пространство
    setForeColor(menu->_sideColor);
    std::wcout << " " << side["L"] << std::endl;

    // "Подвал"
    setForeColor(menu->_sideColor);
    std::wcout << L" " << side["LB"] << side["T"] << L" ";
    setForeColor(menu->_captionColor);
    std::cout << _encode("Выбор: ");

    // Ввод номера пункта
    setForeColor(previousColor);
    int choice;
    while (true) {
        std::string error = "Неверный номер пункта меню";
        readInt(&choice, error, true);
        if (menu->_choose(choice))
            break;
        notification(error, cpe::COLOR_RED);
        pause();
        clear(2);
    }

    // Возврат
    setForeColor(previousColor);
}

void Console::writeTable(Table *table) {
    // Подготовка
    Color previousColor = getForeColor();
    int windowWidth = _getBufferWidth() - 2;
    auto s = tools::define_side_symbols(table->_sideStyle);
    bool outerSide = (table->_displayedSide & cpe::TSIDE_OUTER);
    bool vSide = (table->_displayedSide & cpe::TSIDE_VERTICAL);
    bool hSide = (table->_displayedSide & cpe::TSIDE_HORIZONTAL);

#pragma region ШАПКА - ПЕРВАЯ СТРОКА ТАБЛИЦЫ

    auto row = new Table::_TRow();

    for (auto itHeader = table->_cols.begin();
         itHeader != table->_cols.end();
         itHeader++) {
        row->cells[itHeader->first] = new Table::_TCell();
        row->cells[itHeader->first]->text = itHeader->second->caption;
        row->cells[itHeader->first]->foreColor = table->_headerColor;
    }

    table->_rows.insert(table->_rows.begin(), row);

#pragma endregion

#pragma region КОМПОНОВКА СТОЛБЦОВ

    // Подготовка
    int proportionalSizeSum = 0;            // Сумма пропорциональных размеров (%, не абсолютных)

    // Боковые рамки (слева и с права)
    if (table->_displayedSide & cpe::TSIDE_OUTER)
        windowWidth -= 2;

    // Сумма всех размеров
    for (auto it = table->_cols.begin();
         it != table->_cols.end();
         it++) {
        proportionalSizeSum += (it->second->size < 1) ? 1 : it->second->size;
    }

    // Абсолютные размеры столбцов
    std::map<std::string, int> columnLayoutSizes;

    // Подготовка
    int iColumn = table->_cols.size();
    int allowWidthForColumns = windowWidth - iColumn + 1;
    // Часть доступной области для столбцов
    double partWidth = (double) (allowWidthForColumns) / (double) proportionalSizeSum;
    // Расчет
    for (auto itCol = table->_cols.begin();
         itCol != table->_cols.end();
         itCol++) {
        // Столбец
        auto column = itCol->second;
        // Размер заголовка
        double width = (double) column->size * partWidth;
        int size = std::max((int) std::round(std::min(width, (double) allowWidthForColumns)), 2);
        allowWidthForColumns -= size;
        // Добавление
        columnLayoutSizes[itCol->first] = size;
    }

#pragma endregion

    // Вывод размеров столбцов
    if (_debug) {
        auto debugRow = new Table::_TRow();

        for (auto itCol = table->_cols.begin();
             itCol != table->_cols.end();
             itCol++) {
            debugRow->cells[itCol->first] = new Table::_TCell();
            debugRow->cells[itCol->first]->text = std::to_string(columnLayoutSizes[itCol->first]);
            debugRow->cells[itCol->first]->foreColor = cpe::COLOR_RED;
        }

        table->_rows.insert(table->_rows.begin() + 1, debugRow);
    }

#pragma region ВЫВОД СТРОК

    bool firstRow = true;

    for (auto itRow = table->_rows.begin();
         itRow != table->_rows.end();
         itRow++) {
        auto row = (*itRow);
        int minHeaderLines = 0;                                                // Минимальное кол-во строк в заголовке
        std::map<std::string, std::vector<std::string>> rowCellLines;        // Строки текста ячеек строки таблицы

        // Расчет мин. высоты строки и компановка содержимого ячеек
        for (auto itCol = table->_cols.begin();
             itCol != table->_cols.end();
             itCol++) {
            // Столбец
            auto columnName = itCol->first;
            // Компоновка
            int cellLineWidth = 0;
            int maxLines = table->_maxCellLines;
            if (itCol == table->_cols.begin()) maxLines = table->_maxHeaderLines;
            rowCellLines[columnName] = layout((*itRow)->cells[columnName]->text,
                                              columnLayoutSizes[columnName],
                                              &cellLineWidth,
                                              maxLines,
                                              true);
            // Минимум
            if (minHeaderLines < rowCellLines[columnName].size())
                minHeaderLines = rowCellLines[columnName].size();
        }

        // Вывод каждой строки
        for (int i = 0; i < minHeaderLines; i++) {
            // ЕСЛИ первая строка текста ячейки
            if (i == 0) {
                setForeColor(table->_sideColor);
                // ЕСЛИ первая строка таблицы И флаг "внешняя рамка"
                if (firstRow && outerSide) {
                    std::wcout << " " << s["LT"];

                    // Верхняя рамка
                    for (auto itCol = table->_cols.begin();
                         itCol != table->_cols.end();
                         itCol++) {
                        std::wcout << std::wstring(columnLayoutSizes[itCol->first], s["T"][0]);
                        if (std::distance(itCol, table->_cols.end()) > 1)
                            if (vSide)
                                std::wcout << s["HT"];
                            else
                                std::wcout << s["T"];
                    }

                    std::wcout << s["RT"];
                    std::wcout << std::endl;
                }
                    // ЕСЛИ флаг "верт. разделитель"
                else if (!firstRow && hSide) {
                    std::cout << " ";
                    if (outerSide)
                        std::wcout << s["VL"];

                    // Верхняя рамка
                    for (auto itCol = table->_cols.begin();
                         itCol != table->_cols.end();
                         itCol++) {
                        std::wcout << std::wstring(columnLayoutSizes[itCol->first], s["H"][0]);
                        if (std::distance(itCol, table->_cols.end()) > 1)
                            if (vSide)
                                std::wcout << s["+"];
                            else
                                std::wcout << s["H"];
                    }

                    if (outerSide)
                        std::wcout << s["VR"];
                    std::wcout << std::endl;
                }

                firstRow = false;
            }

            std::wcout << " ";

            // Вывод текущей строки
            bool firstColumn = true;
            for (auto itCol = table->_cols.begin();
                 itCol != table->_cols.end();
                 itCol++) {
                auto columnName = itCol->first;

                // Левая рамка
                if (outerSide && firstColumn) {
                    setForeColor(table->_sideColor);
                    std::wcout << s["L"];
                    firstColumn = false;
                }

                // Вывод строки ячейки
                setForeColor(row->cells[columnName]->foreColor);
                if (i < rowCellLines[columnName].size())
                    std::cout << _encode(rowCellLines[columnName][i]);
                else
                    std::wcout << std::wstring(columnLayoutSizes[columnName], L' ');

                // Правая рамка
                setForeColor(table->_sideColor);
                if (std::distance(itCol, table->_cols.end()) > 1) {
                    // Внутри вертикальная
                    if (vSide)
                        std::wcout << s["V"];
                        // Или пробел
                    else
                        std::cout << " ";
                } else {
                    // Внешняя правая
                    if (outerSide)
                        std::wcout << s["R"];
                }
            }

            std::cout << std::endl;
        }
    }

    // ЕСЛИ флаг "внешняя рамка", ТО вывод нижней рамки
    if (outerSide) {
        setForeColor(table->_sideColor);
        std::wcout << " " << s["LB"];

        // Верхняя рамка
        for (auto itCol = table->_cols.begin();
             itCol != table->_cols.end();
             itCol++) {
            std::wcout << std::wstring(columnLayoutSizes[itCol->first], s["B"][0]);
            if (std::distance(itCol, table->_cols.end()) > 1)
                if (vSide)
                    std::wcout << s["HB"];
                else
                    std::wcout << s["B"];
        }

        std::wcout << s["RB"];
        std::wcout << std::endl;
    }

    setForeColor(previousColor);

#pragma endregion

}


void Console::pause() {
    _addLastCurPos();
    system("pause");
    clear(1);
}


void Console::clear() {
    _lastCursorPositions.clear();
    system("cls");
}

void Console::clear(int parts) {
    if (parts > _lastCursorPositions.size())
        parts = _lastCursorPositions.size();
    auto last = _lastCursorPositions.end() - parts;

    if (last == _lastCursorPositions.end())
        return;

    _clear(_getCursorPosition(), *last);
    _lastCursorPositions.erase(last, _lastCursorPositions.end());
}

void Console::resetForeColor() {
    setForeColor(_defaultForeColor);
}

void Console::addOutputPart() {
    _addLastCurPos();
}

int Console::outputPartCount() const {
    return _lastCursorPositions.size();
}


void Console::setForeColor(Color color) {
    if (color == Color::COLOR_DEFAULT)
        color = _defaultForeColor;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    _foreColor = color;
}

Color Console::getForeColor() const {
    return _foreColor;
}

void Console::setDefaultForeColor(Color color) {
    if (color == Color::COLOR_DEFAULT)
        color = Color::COLOR_WHITE;
    _defaultForeColor = color;
}

Color Console::getDefaultForeColor() const {
    return _defaultForeColor;
}

void Console::setCpInput(int codePage) {
    _cpInput = codePage;
}

int Console::getCpInput() const {
    return _cpInput;
}

void Console::setCpOutput(int codePage) {
    _cpOutput = codePage;
}

int Console::getCpOutput() const {
    return _cpOutput;
}

void Console::setUnfinished(std::string value) {
    _unfinished = value;
}

std::string Console::getUnfinished() const {
    return _unfinished;
}

void Console::setTabLength(int size) {
    _tabSize = size;
}

int Console::getTabLength() const {
    return _tabSize;
}

void Console::setWindowTitle(std::string title) {
    _title = title;
    system(std::string("title " + title).c_str());
}

std::string Console::getWindowTitle() const {
    return _title;
}


std::vector<std::string> Console::layout(
        std::string src,
        int width,
        int *outMaxWidth,
        int maxHeight,
        bool fill) const {
    // Подготовка
    std::vector<std::string> lines;
    std::string line;
    int mw = 0;

    // Если нет ограничения
    if (width <= 0) {
        if (outMaxWidth != nullptr)
            *outMaxWidth = (int)src.size();
        lines.push_back(src);
        return lines;
    }
    // Деление строки
    for (int i = 0; i < src.size(); i++) {
        char c = src[i];

        // Добавление в строку
        if (c != '\n' && c != '\t')
            line += c;
        // Табуляция
        if (c == '\t') {
            // Расстояние до след. таба
            int nextTab = _tabSize - ((int)line.size() % _tabSize);
            // ЕСЛИ расстояние не превышает ширину
            if (line.size() + nextTab < width)
                line += std::string((size_t)nextTab, ' ');
            else
                c = '\n';
        }
        // Новая строка
        bool isSrcEnd = (i + 1 == src.size());
        if (c == '\n' || line.size() >= width || isSrcEnd) {
            // Заполнение
            if (fill)
                line += std::string(width - line.size(), ' ');

            // ЕСЛИ последняя строка
            if (maxHeight != 0 && lines.size() + 1 == maxHeight && !isSrcEnd) {
                line = line.substr(0, width - _unfinished.size());
                line += _unfinished;
            }
            // Макс. длина
            if (mw < line.size())
                mw = (int)line.size();
            // Добавление
            lines.push_back(line);
            // ЕСЛИ последняя строка
            if (lines.size() == maxHeight)
                break;

            line.clear();
        }
    }

    // Возврат
    if (outMaxWidth != nullptr)
        *outMaxWidth = mw;
    return lines;
}

void Console::debug(bool enabled) {
    _debug = enabled;
}


std::string Console::_encode(std::string src) {
    return tools::encode(_cpInput, _cpOutput, std::move(src));
}

std::string Console::_decode(std::string src) {
    return cpe::tools::encode(_cpOutput, _cpInput, std::move(src));
}


void Console::_setCursorPosition(COORD crd) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, crd);
}

COORD Console::_getCursorPosition() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void Console::_moveCursor(short x, short y) {
    auto coord = _getCursorPosition();
    coord.X += x;
    coord.Y += y;
    _setCursorPosition(coord);
}

void Console::_addLastCurPos() {
    _lastCursorPositions.push_back(_getCursorPosition());
}

int Console::_getBufferWidth() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwSize.X;
}

void Console::_clear(COORD begin, COORD end) {
    // Инф. о консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    if (begin.Y > end.Y || begin.X > end.X) {
        COORD swaper = begin;
        begin = end;
        end = swaper;
    }

    _setCursorPosition(begin);
    int count = (csbi.dwSize.X - begin.X) + end.X + (end.Y - begin.Y - 1) * csbi.dwSize.X;
    std::cout << std::string((size_t)count, ' ');
    _setCursorPosition(begin);
}

}