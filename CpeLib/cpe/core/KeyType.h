#pragma once

namespace cpe::core {

/**
 * Типы клавишь
 */
enum class KeyType : int {
    Unknown = -2,
    Symbol = -1,
    ArrowUp = 1,
    ArrowDown = 2,
    ArrowLeft = 3,
    ArrowRight = 4
};

}
