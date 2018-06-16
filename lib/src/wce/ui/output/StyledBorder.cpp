#include "StyledBorder.h"
#include "StyledChar.h"

namespace wce {

StyledBorder::StyledBorder(const BorderStyle &border) : style(border) { }

StyledBorder::StyledBorder(const BorderStyle &border, const TextColor &color) : style(border), color(color) { }

StyledChar StyledBorder::at(const BorderStyle::Side &side) const {
    return StyledChar(style.at(side), color);
}

StyledChar StyledBorder::operator[](const BorderStyle::Side &side) const {
    return at(side);
}

}


