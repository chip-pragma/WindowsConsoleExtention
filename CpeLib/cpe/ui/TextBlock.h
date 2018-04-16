#pragma once

#include <string>
#include <vector>

#include "cpe/core/io/AWriter.h"


namespace cpe::ui {

using namespace cpe::core;

/**
 * Форматированный текст в ограниченном прямоугольнике
 */
class TextBlock : public AbstractWriter {
public:
    /**
     * Создает форматированный текст по заданным параметров из исходной строки
     * @param source Исходная строка
     * @param outputFormat Длинна табуляции (в пробелах)
     * @param maxWidth Максимальная допустимая ширина строки текста (в символах). Должна быть больше 0
     * @param maxHeight Максимальная допустимая высота текста (в строках). 0 - без ограничений
     * @return Объект форматированного текста StringText
     */
    TextBlock(std::string *source, int maxWidth, int maxHeight);

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

private:
    // Информация о пропуске строки
    class _Line;

    TextBlock();

    std::string _source;
    uint8_t _width;
    bool _placed;
    bool _fillToWidth;

    // Массив перевода строк текста
    std::vector<_Line> _lines;
};

}