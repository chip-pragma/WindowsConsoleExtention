#ifndef CONSOLEPRESENTEXTENTION_STRINGTEXT_H
#define CONSOLEPRESENTEXTENTION_STRINGTEXT_H

#include <string>
#include <vector>

namespace cpe {

/**
 * Форматированный текст
 */
class StringText {
public:
    /**
     * Создает форматированный текст по заданным параметров из исходной строки
     * @param source Исходная строка
     * @param tabLength Длинна табуляции (в пробелах)
     * @param maxWidth Максимальная допустимая ширина строки текста (в символах). Должна быть больше 0
     * @param maxHeight Максимальная допустимая высота текста (в строках). 0 - без ограничений
     * @return Объект форматированного текста {@link StringText}
     */
    static StringText *create(std::string *const source, int tabLength, int maxWidth, int maxHeight);

    ~StringText();

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
    int getWidth() const;
    /**
     * Возвращает итоговую высоту форматированного текста (в строках)
     */
    int getHeight() const;

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


private:
    // Информация о пропуске строки
    class _Line;

    StringText();

    std::string _source;
    int _width;
    bool _placed;
    bool _fillToWidth;

    // Массив перевода строк текста
    std::vector<_Line> _lines;
};

}


#endif //CONSOLEPRESENTEXTENTION_LAYOUTTEXT_H
