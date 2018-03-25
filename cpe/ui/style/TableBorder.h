

#ifndef PROJECT_TABLEBORDER_H
#define PROJECT_TABLEBORDER_H

namespace cpe::ui::style {

/**
 * Стиль отображения рамок таблицы
 */
enum class TableBorder {
    // Нет рамок
    NONE = 0,
    // Только вертикальные
    VERTICAL = 1,
    // Только горизонтальные
    HORIZONTAL = 2,
    OUTER = 4,
    INNER = 3,
    ALL = 7
};

}

#endif //PROJECT_TABLEBORDER_H
