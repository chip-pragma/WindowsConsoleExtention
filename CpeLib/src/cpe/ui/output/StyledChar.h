#pragma once

#include "cpe/core/draw/Color.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

class StyledChar {
public:
    StyledChar();

    StyledChar(char c);

    StyledChar(char c, const TextColor& color);

    StyledChar(const StyledChar &sch);

    StyledChar(StyledChar &&sch) noexcept;

    const TextColor &color() const;

    TextColor &color();

    void color(const TextColor &color);

    char character() const;

    void character(char aChar);

    StyledChar &operator=(const StyledChar &sch);

private:
    TextColor mColor;
    char mChar = ' ';
};

}



