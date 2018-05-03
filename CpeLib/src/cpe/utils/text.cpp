#include "text.h"

#include <stdexcept>

namespace cpe::text {

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

int replace(std::string &source, const std::string &from, const std::string &to) {
    if(from.empty())
        return 0;
    size_t start_pos = 0;
    while((start_pos = source.find(from, start_pos)) != std::string::npos) {
        source.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

}