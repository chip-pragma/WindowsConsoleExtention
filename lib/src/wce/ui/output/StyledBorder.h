#pragma once

#include "wce/ui/style/TextColor.h"
#include "wce/ui/style/BorderStyle.h"
#include "StyledChar.h"

namespace wce {

class StyledBorder {
public:
    TextColor color;
    BorderStyle style;

    StyledBorder() = default;

    explicit StyledBorder(const BorderStyle& border);

    StyledBorder(const BorderStyle& border, const TextColor& color);

    StyledChar at(const BorderStyle::Side &side) const;

    StyledChar operator[](const BorderStyle::Side &side) const;
};

}




