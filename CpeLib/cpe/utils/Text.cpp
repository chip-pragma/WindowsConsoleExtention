#include "Text.h"

#include <stdexcept>

namespace cpe::utils::text {

void trim(std::string &src) {
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

void split(const std::string &src,
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