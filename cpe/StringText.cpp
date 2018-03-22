#include "StringText.h"

namespace cpe {

class StringText::_Line {
public:
    // Длина строки
    int length;
    // Содержит перевод строки в исходной строке
    bool isWrap;

    _Line() {
        length = 0;
        isWrap = false;
    }
};

StringText *StringText::create(std::string *const source, int tabLength, int maxWidth, int maxHeight) {
    if (maxWidth <= 0)
        return nullptr;

    // Создание объекта
    auto st = new StringText();
    st->_source = std::string(*source);
    st->_placed = true;
    st->_width = 0;
    // Максимальная итоговая ширина
    _Line line;

    // Деление строки
    for (int i = 0, n = source->size(); i < n; ++i) {
        char c = (*source)[i];

        if (c != '\n' && c != '\t')
            line.length++;
        // Табуляция
        if (c == '\t') {
            // Расстояние до след. таба
            int nextTab = tabLength - (line.length % tabLength);
            // ЕСЛИ расстояние не превышает ширину
            if (line.length + nextTab < maxWidth)
                line.length += nextTab;
            else {
                // ИНАЧЕ новая строка
                st->_lines.push_back(line);
                line = _Line();
            }
        }
        // Новая строка
        bool isSrcEnd = (i + 1 == n);
        if (c == '\n' || line.length >= maxWidth || isSrcEnd) {
            line.isWrap = (c == '\n');
            // ЕСЛИ последняя строка
            if (maxHeight != 0 && st->_lines.size() + 1 == maxHeight && !isSrcEnd) {
                st->_placed = false;
            }
            // Макс. длина
            if (st->_width < line.length)
                st->_width = line.length;
            // Добавление
            st->_lines.push_back(line);
            line = _Line();
            // ЕСЛИ последняя строка
            if (st->_lines.size() == maxHeight)
                break;
        }
    }

    return st;
}

StringText::StringText() = default;

std::vector<std::string> StringText::toVector() {

}

std::string StringText::toString() {

}

const std::string &StringText::getSource() const {
    return _source;
}

int StringText::getWidth() const {
    return _width;
}

int StringText::getHeight() const {
    return _lines.size();
}

bool StringText::isFillToWidth() const {
    return _fillToWidth;
}

void StringText::setFillToWidth(bool fillToWidth) {
    _fillToWidth = fillToWidth;
}

StringText::~StringText() {

}

bool StringText::isPlaced() const {
    return _placed;
}


}