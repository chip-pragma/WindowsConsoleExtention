#include "StyledBorder.h"
#include "StyledChar.h"

namespace cpe {

StyledBorder::StyledBorder(const Border &border) : mBorder(border) {

}

StyledBorder::StyledBorder(const Border &border, const TextColor &color) : mBorder(border), mColor(color) {

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

const Border &StyledBorder::border() const {
    return mBorder;
}

Border &StyledBorder::border() {
    return mBorder;
}

StyledChar StyledBorder::at(const Border::Side &side) const {
    return StyledChar(mBorder.at(side), mColor);
}

StyledChar StyledBorder::operator[](const Border::Side &side) const {
    return at(side);
}

}


