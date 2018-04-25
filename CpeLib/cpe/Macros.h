#pragma once

/**
 * Проверяет во время компиляции корректное наследование типов
 * @param base Базовый тип
 * @param child Дочерний тип
 */
#define CPE__STATIC_CHECK_BASE_CLASS(base, child) \
static_assert( \
    std::is_base_of<base, child>::value, \
    "'"#base"' is not base for '"#child"'");
