#include "StyledBorder.h"
#include "StyledChar.h"

namespace wce {

StyledBorder::StyledBorder(const BorderStyle &border) : mBorder(border) {

}

StyledBorder::StyledBorder(const BorderStyle &border, const TextColor &color) : mBorder(border), mColor(color) {

}

const TextColor &StyledBorder::getColor() const {
    return mColor;
}

TextColor &StyledBorder::getColorRef() {
    return mColor;
}

const BorderStyle &StyledBorder::getStyle() const {
    return mBorder;
}

BorderStyle &StyledBorder::getStyleRef() {
    return mBorder;
}

StyledChar StyledBorder::at(const BorderStyle::Side &side) const {
    return StyledChar(mBorder.at(side), mColor);
}

StyledChar StyledBorder::operator[](const BorderStyle::Side &side) const {
    return at(side);
}

}


