#include "StyledBorder.h"
#include "StyledChar.h"

namespace cpe {

StyledBorder::StyledBorder(const BorderStyle &border) : mBorder(border) {

}

StyledBorder::StyledBorder(const BorderStyle &border, const TextColor &color) : mBorder(border), mColor(color) {

}

const TextColor &StyledBorder::color() const {
    return mColor;
}

TextColor &StyledBorder::color() {
    return mColor;
}

void StyledBorder::color(const TextColor &color) {
    mColor = color;
}

const BorderStyle &StyledBorder::style() const {
    return mBorder;
}

BorderStyle &StyledBorder::style() {
    return mBorder;
}

StyledChar StyledBorder::at(const BorderStyle::Side &side) const {
    return StyledChar(mBorder.at(side), mColor);
}

StyledChar StyledBorder::operator[](const BorderStyle::Side &side) const {
    return at(side);
}

}


