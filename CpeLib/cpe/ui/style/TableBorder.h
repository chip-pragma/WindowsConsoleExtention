

#ifndef PROJECT_TABLEBORDER_H
#define PROJECT_TABLEBORDER_H

namespace cpe::ui::style {

/**
 * Стиль отображения рамок таблицы
 */
enum class TableBorder : char {
    /** Нет рамок */
            NONE = 0,
    /** Вертикальные */
            VERTICAL = 1,
    /** Горизонтальные */
            HORIZONTAL = 2,
    /** Внешние */
            OUTER = 4,
    /** Внутренние */
            INNER = 3,
    /** Все рамки */
            ALL = 7
};

}

#endif //PROJECT_TABLEBORDER_H
