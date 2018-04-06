//
// Created by chip_pragma on 25.03.2018.
//

#include <stdexcept>

#include "Text.h"

namespace cpe::utils {

void Text::trim(std::string &src) {
    auto i = src.begin();
    for (; i != src.end(); i++) {
        char c = *i;
        if (!(c == ' ' || c == '\n' || c == '\t' || c == '\r')) break;
    }
    // Удаление
    src.erase(src.begin(), i);

    auto j = src.rbegin();
    for (; j != src.rend(); j++) {
        char c = *j;
        if (!(c == ' ' || c == '\n' || c == '\t' || c == '\r')) break;
    }
    // Удаление
    src.erase(j.base(), src.rbegin().base());
}

void Text::split(const std::string& src,
                 std::vector<std::string> &dest,
                 const std::string &anyDelim) {
    if (anyDelim.empty() || src.empty())
        return;

    // Подготовка
    std::string line;

    // Деление
    char srcLast = src[src.size() - 1];
    for (auto iSrc : src) {
        bool separator = (anyDelim.find(iSrc) != std::string::npos);

        if (!separator) {
            line += iSrc;
        }

        if (separator || iSrc == srcLast) {
            if (!line.empty())
                dest.push_back(line);
            line.clear();
        }
    }
}

}