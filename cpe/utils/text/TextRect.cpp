#include "TextRect.h"

namespace cpe::utils::text {

class TextRect::_Line {
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

TextRect *TextRect::create(std::string *const source, int tabLength, int maxWidth, int maxHeight) {
    if (maxWidth <= 0)
        return nullptr;

    // Создание объекта
    auto st = new TextRect();
    st->_source = std::string(*source);
    st->_placed = true;
    st->_width = 0;
    // Максимальная итоговая ширина
    _Line line;

    // Деление строки
    for (int i = 0, n = (int)source->size(); i < n; ++i) {
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

TextRect::TextRect() = default;

std::vector<std::string> TextRect::toVector() {
    // Подготовка
    std::vector<std::string> resultLines;
    int pos = 0;
    // Запись строк
    for (int i = 0, n = (int)_lines.size(); i < n; ++i) {
        // Получение строки из исходной
        auto formatLine = _lines[i];
        auto line = _source.substr((size_t) pos, (size_t) formatLine.length);
        // Заполнение пробелов
        if (_fillToWidth)
            line += std::string(static_cast<size_t>(_width - formatLine.length), ' ');
        // Добавление "незавершенности"
        if (!_placed && i+1 == n) {
            line = line.substr(0, _width - _unfinished.size());
            line += _unfinished;
        }
        // Сдвиг курсора
        pos += formatLine.length;
        if (formatLine.isWrap)
            pos++;

        resultLines.push_back(line);
    }
    return resultLines;
}

std::string TextRect::toString() {

}

const std::string &TextRect::getSource() const {
    return _source;
}

int TextRect::getWidth() const {
    return _width;
}

int TextRect::getHeight() const {
    return _lines.size();
}

bool TextRect::isFillToWidth() const {
    return _fillToWidth;
}

void TextRect::setFillToWidth(bool fillToWidth) {
    _fillToWidth = fillToWidth;
}

TextRect::~TextRect() {

}

bool TextRect::isPlaced() const {
    return _placed;
}


}