//
// Created by chip_pragma on 25.03.2018.
//

#include <stdexcept>

#include "Text.h"

namespace cpe::utils {

void Text::trim(std::string *src) {
    auto i = src->begin();
    for (; i != src->end(); i++) {
        char c = *i;
        if (!(c == ' ' || c == '\n' || c == '\t' || c == '\r')) break;
    }
    // Удаление
    src->erase(src->begin(), i);

    auto j = src->rbegin();
    for (; j != src->rend(); j++) {
        char c = *j;
        if (!(c == ' ' || c == '\n' || c == '\t' || c == '\r')) break;
    }
    // Удаление
    src->erase(j.base(), src->rbegin().base());
}

void Text::split(std::string src, std::vector<std::string> *dest, std::string anyDelim) {
    if (dest == nullptr)
        throw std::runtime_error("Не указан выходной массив <dest>");
    if (anyDelim.empty())
        return;

    // Подготовка
    std::string line;

    // Деление
    for (auto iSrc = src.begin();
         iSrc != src.end();
         iSrc++) {
        bool separator = false;
        // Сравнение
        for (auto iDelim = anyDelim.begin();
             iDelim != anyDelim.end();
             iDelim++) {
            if (*iSrc == *iDelim) {
                separator = true;
                break;
            }
        }
        // Получение символа
        if (!separator) {
            line += *iSrc;
        }

        if (separator || iSrc + 1 == src.end()) {
            if (line.size() > 0)
                dest->push_back(line);
            line.clear();
        }
    }
}

}