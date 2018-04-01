#include "TextBlock.h"
#include "style/TextStyle.h"

namespace cpe::ui {

using TextStyle = style::TextStyle;

class TextBlock::_Line {
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

TextBlock::TextBlock(std::string *source, const TextStyle& textStyle, int maxWidth, int maxHeight = 0) {
    // Создание объекта
    _source = std::string(*source);
    _placed = true;
    _width = 0;
    _textStyle = textStyle;
    // Максимальная итоговая ширина
    _Line line;

    // Деление строки
    for (int i = 0, n = (int) source->size(); i < n; ++i) {
        char c = (*source)[i];

        if (c != '\n' && c != '\t')
            line.length++;
        // Табуляция
        if (c == '\t') {
            // Расстояние до след. таба
            int nextTab = _textStyle.getTabLength() - (line.length % _textStyle.getTabLength());
            // ЕСЛИ расстояние не превышает ширину
            if (line.length + nextTab < maxWidth)
                line.length += nextTab;
            else {
                // ИНАЧЕ новая строка
                _lines.push_back(line);
                line = _Line();
            }
        }
        // Новая строка
        bool isSrcEnd = (i + 1 == n);
        if (c == '\n' || line.length >= maxWidth || isSrcEnd) {
            line.isWrap = (c == '\n');
            // ЕСЛИ последняя строка
            if (maxHeight != 0 && _lines.size() + 1 == maxHeight && !isSrcEnd) {
                _placed = false;
            }
            // Макс. длина
            if (_width < line.length)
                _width = (uint8_t)line.length;
            // Добавление
            _lines.push_back(line);
            line = _Line();
            // ЕСЛИ последняя строка
            if (_lines.size() == maxHeight)
                break;
        }
    }
}

TextBlock::TextBlock() = default;

std::vector<std::string> TextBlock::toVector() {
    // Подготовка
    std::vector<std::string> resultLines;
    int pos = 0;
    // Запись строк
    for (int i = 0, n = (int) _lines.size(); i < n; ++i) {
        // Получение строки из исходной
        _Line formatLine = _lines[i];
        auto line = _source.substr((size_t) pos, (size_t) formatLine.length);
        // Заполнение пробелов
        if (_fillToWidth)
            line += std::string(static_cast<size_t>(_width - formatLine.length), ' ');
        // Добавление "незавершенности"
        if (!_placed && i + 1 == n) {
            line = line.substr(0, _width - _textStyle.getUnfinished().size());
            line += _textStyle.getUnfinished();
        }
        // Сдвиг курсора
        pos += formatLine.length;
        if (formatLine.isWrap)
            pos++;

        resultLines.push_back(line);
    }
    return resultLines;
}

std::string TextBlock::toString() {

}

const std::string &TextBlock::getSource() const {
    return _source;
}

uint8_t TextBlock::getWidth() const {
    return _width;
}

uint32_t TextBlock::getHeight() const {
    return (uint32_t)_lines.size();
}

bool TextBlock::isFillToWidth() const {
    return _fillToWidth;
}

void TextBlock::setFillToWidth(bool fillToWidth) {
    _fillToWidth = fillToWidth;
}

bool TextBlock::isPlaced() const {
    return _placed;
}

const TextStyle &TextBlock::getTextStyle() const {
    return _textStyle;
}


}