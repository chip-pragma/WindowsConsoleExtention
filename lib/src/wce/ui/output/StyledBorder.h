#pragma once

#include "wce/ui/style/TextColor.h"
#include "wce/ui/style/BorderStyle.h"
#include "StyledChar.h"

namespace wce {

class StyledBorder {
public:
    StyledBorder() = default;

    explicit StyledBorder(const BorderStyle& border);

    StyledBorder(const BorderStyle& border, const TextColor& color);

    const TextColor &getColor() const;

    TextColor &getColorRef();

    const BorderStyle& getStyle() const;

    BorderStyle& getStyleRef();

    StyledChar at(const BorderStyle::Side &side) const;

    StyledChar operator[](const BorderStyle::Side &side) const;

private:
    TextColor mColor;
    BorderStyle mBorder;
};

}




