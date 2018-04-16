#pragma once

namespace cpe::ui::style {

/**
 * Использование двойных рамок
 */
enum class DualBorder : unsigned char {
    /// Нет двойных
            NONE = 0,
    // Слева внешняя
            LEFT = 1 << 0,
    // Справа внешняя
            RIGHT = 1 << 1,
    // Сверху внешняя
            TOP = 1 << 2,
    // Снизу внешняя
            BOTTOM = 1 << 3,
    // Вертикальные (слева и справа) внешние
            OUT_V = (int) (LEFT | RIGHT),
    // Горизонтальные (снизу и сверху) внешние
            OUT_H = (int) (TOP | BOTTOM),
    /// Двойные внешние
            OUT_ALL = (int) (OUT_V | OUT_H),
    // Вертикальные внутренние
            IN_V = 1 << 4,
    // Горизонтальные внутренние
            IN_H = 1 << 5,
    // Двойные внутренние
            IN_ALL = (int) (IN_V | IN_H),
    // Все рамки двойные
            ALL = (int) (OUT_ALL | IN_ALL)
};

DualBorder operator&(const DualBorder &db1, const DualBorder &db2) {
    return (DualBorder) ((unsigned char) db1 & (unsigned char) db2);
}

DualBorder operator|(const DualBorder &db1, const DualBorder &db2) {
    return (DualBorder) ((unsigned char) db1 | (unsigned char) db2);
}

}
