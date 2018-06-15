#pragma once

namespace cpe {

enum class TableBorder : char {
    NONE = 0,
    VERTICAL = 1,
    HORIZONTAL = 2,
    OUTER = 4,
    INNER = 3,
    ALL = 7
};

}
