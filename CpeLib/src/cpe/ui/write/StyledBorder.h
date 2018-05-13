#pragma once

#include "cpe/ui/style/TextColor.h"
#include "cpe/ui/style/Border.h"
#include "cpe/ui/write/StyledChar.h"

namespace cpe {

class StyledBorder {
public:
    StyledBorder() = default;

    explicit StyledBorder(const Border& border);

    StyledBorder(const Border& border, const TextColor& color);

    const TextColor &color() const;

    TextColor &color();

    void color(const TextColor &color);

    const Border& border() const;

    Border& border();

    StyledChar at(const Border::Side &side) const;

    StyledChar operator[](const Border::Side &side) const;

private:
    TextColor mColor;
    Border mBorder;
};

}




