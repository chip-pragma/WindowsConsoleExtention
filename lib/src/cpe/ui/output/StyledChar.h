#pragma once

#include "cpe/core/draw/Color.h"
#include "cpe/ui/style/TextColor.h"

namespace wce {

class StyledChar {
public:
    StyledChar();

    StyledChar(char c);

    StyledChar(char c, const TextColor& color);

    StyledChar(const StyledChar &sch);

    StyledChar(StyledChar &&sch) noexcept;

    const TextColor &getColor() const;

    TextColor &getColorRef();

    char getChar() const;

    void setChar(char aChar);

    StyledChar &operator=(const StyledChar &sch);

private:
    TextColor mColor;
    char mChar = ' ';
};

}



