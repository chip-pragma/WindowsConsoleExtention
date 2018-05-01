#pragma once

#include <type_traits>

/**
 * Проверяет во время компиляции корректное наследование типов
 * @param base Базовый тип
 * @param child Дочерний тип
 */
#define CPE_MACROS_StaticCheckBaseClass(base, child) \
static_assert( \
    std::is_base_of<base, child>::value, \
    "'"#base"' is not base for '"#child"'")
