#pragma once

#include <cstdint>

namespace cpe {

/**
 * Использование двойных рамок
 */
enum class DualBorder : uint8_t {
    NONE = 0,
    LEFT = 1 << 0,
    RIGHT = 1 << 1,
    TOP = 1 << 2,
    BOTTOM = 1 << 3,
    OUT_V = static_cast<int>(LEFT | RIGHT),
    OUT_H = static_cast<int>(TOP | BOTTOM),
    OUT_ALL = static_cast<int>(OUT_V | OUT_H),
    IN_V = 1 << 4,
    IN_H = 1 << 5,
    IN_ALL = static_cast<int>(IN_V | IN_H),
    ALL = static_cast<int>(OUT_ALL | IN_ALL)
};


bool operator==(const DualBorder &db, int32_t i);

bool operator!=(const DualBorder &db, int32_t i);

DualBorder operator&(const DualBorder &db1, const DualBorder &db2);

DualBorder operator|(const DualBorder &db1, const DualBorder &db2);


}
