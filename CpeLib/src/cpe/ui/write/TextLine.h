#pragma once

#include <cstdint>
#include <string>
#include <algorithm>
#include <vector>

#include "StyledChar.h"

namespace cpe {

// TODO избавиться от изменения значений (убрать наследование от vector и добавить динамический массив)

class TextLine : public std::vector<StyledChar>{
public:
    explicit TextLine(size_type length);

    TextLine(const TextLine &line);

    size_type get_last() const;

    void set_as_unfinished(const std::string &unfinished);

    value_type &operator[](size_type index);

private:
    size_type mLast = 0;
};

}

