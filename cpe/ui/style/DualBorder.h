#ifndef PROJECT_BORDERSTYLE_H
#define PROJECT_BORDERSTYLE_H

#include "Style.h"

namespace cpe::ui::style {

/**
 * Использование двойных рамок
 */
enum class DualBorder : FlagsByte {
    // Нет двойных
            NONE = 1 << 0,
    // Слева внешняя
            LEFT = 1 << 1,
    // Справа внешняя
            RIGHT = 1 << 2,
    // Сверху внешняя
            TOP = 1 << 3,
    // Снизу внешняя
            BOTTOM = 1 << 4,
    // Вертикальные (слева и справа) внешние
            OUT_V = LEFT | RIGHT,
    // Горизонтальные (снизу и сверху) внешние
            OUT_H = TOP | BOTTOM,
    // Двойные внешние
            OUT_ALL = OUT_V | OUT_H,
    // Вертикальные внутренние
            IN_V = 1 << 5,
    // Горизонтальные внутренние
            IN_H = 1 << 6,
    // Двойные внутренние
            IN_ALL = IN_V | IN_H,
    // Все рамки двойные
            ALL = OUT_ALL | IN_ALL
};

}

#endif //PROJECT_BORDERSTYLE_H
