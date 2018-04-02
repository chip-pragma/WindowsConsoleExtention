#ifndef CONSOLEPRESENTEXTENTION_STRINGTEXT_H
#define CONSOLEPRESENTEXTENTION_STRINGTEXT_H

#include <string>
#include <vector>

namespace cpe::ui {

namespace {
class TextStyle;
}

/**
 * Форматированный текст в ограниченном прямоугольнике
 */
class TextBlock {
public:
    /**
     * Создает форматированный текст по заданным параметров из исходной строки
     * @param source Исходная строка
     * @param textStyle Длинна табуляции (в пробелах)
     * @param maxWidth Максимальная допустимая ширина строки текста (в символах). Должна быть больше 0
     * @param maxHeight Максимальная допустимая высота текста (в строках). 0 - без ограничений
     * @return Объект форматированного текста StringText
     */
    TextBlock(std::string *source, const TextStyle& textStyle, int maxWidth, int maxHeight);

    /**
     * Записывает строки текств в вектор
     * @return Вектор со строками текста
     */
    std::vector<std::string> toVector();

    /**
     * Записывает форматированный текст в итоговую строку
     * @return Итоговая строка из форматированного текста
     */
    std::string toString();

    /**
     * Возвращает исходную неформатированнаую строку
     */
    const std::string &getSource() const;

    /**
     * Возвращает итоговую ширину форматированного теста (в символах)
     */
    uint8_t getWidth() const;
    /**
     * Возвращает итоговую высоту форматированного текста (в строках)
     */
    uint32_t getHeight() const;

    /**
     * Поместилась исходная строка в заданный блок форматированного текста?
     */
    bool isPlaced() const;

    /**
     * Возвращает значение флага заполнения строк пробелами, если те не равны итоговой ширине
     */
    bool isFillToWidth() const;

    /**
     * Задает флаг заполнения строк пробелами, если те не равны итоговой ширине
     * @param fillToWidth true, сли необходимо заполнение. Иначе false
     */
    void setFillToWidth(bool fillToWidth);

    /**
     * Возвращает стиль текста, используемый при форматированиии блока текста
     */
    const TextStyle &getTextStyle() const;


private:
    // Информация о пропуске строки
    class _Line;

    TextBlock();

    std::string _source;
    uint8_t _width;
    bool _placed;
    bool _fillToWidth;
    extern TextStyle _textStyle;

    // Массив перевода строк текста
    std::vector<_Line> _lines;
};

}


#endif //CONSOLEPRESENTEXTENTION_LAYOUTTEXT_H
