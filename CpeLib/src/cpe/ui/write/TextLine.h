#pragma once

#include <cstdint>
#include <string>
#include <algorithm>
#include <vector>

#include "TextChar.h"

namespace cpe {

// TODO избавиться от изменения значений (убрать наследование от vector и добавить динамический массив)

class TextLine : public std::vector<TextChar>{
public:
    explicit TextLine(size_type length);

    TextLine(const TextLine &line);

    size_type getLast() const;

    void setAsUnfinished(const std::string &unfinished);

    value_type &operator[](size_type index);

private:
    size_type mLast = 0;
};

}

