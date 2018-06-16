#pragma once

#include "wce/ui/style/TextColor.h"

namespace wce {

class StyledChar {
public:
    TextColor color;
    char character = ' ';

    StyledChar();

    StyledChar(char c); // NOLINT

    StyledChar(char c, const TextColor& color);

    StyledChar(const StyledChar &sch);

    StyledChar(StyledChar &&sch) noexcept;

    StyledChar &operator=(const StyledChar &sch);
};

}



