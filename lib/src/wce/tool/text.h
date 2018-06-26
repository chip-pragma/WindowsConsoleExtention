#pragma once

#include <string>
#include <vector>

namespace wce::text {

/**
 * Удаление начальных и конечных знаков пробелов
 * @param src Обрабатываемая строка
 */
void trim(std::string &src);

/**
 * Деление строки по указанным делителям
 * @param src Исходная делимая строка
 * @param dest Конечный вектор разделенной строки
 * @param anyDelim Последовательность делителей
 */
void split(const std::string &src,
           std::vector<std::string> &dest,
           const std::string &anyDelim);

size_t replace(std::string &source, const std::string &from, const std::string &to);
};

