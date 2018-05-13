#pragma once

#include "cpe/core/draw/Color.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

class StyledChar {
public:
    StyledChar() = default;

    explicit StyledChar(char c);

    StyledChar(char c, const TextColor& color);

    const TextColor &color() const;

    TextColor &color();

    void color(const TextColor &color);

    char character() const;

    void character(char aChar);

private:
    TextColor mColor;
    char mChar = ' ';
};

}



