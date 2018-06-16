#include "TextColor.h"

#include <utility>

namespace wce {

TextColor::TextColor() {

}

TextColor::TextColor(const std::optional<ColorIndex> fore, const std::optional<ColorIndex> back) {
    foreground = fore;
    background = back;
}

TextColor::TextColor(const TextColor &tc) {
    foreground = tc.foreground;
    background = tc.background;
}

TextColor::TextColor(TextColor &&tc) noexcept {
    foreground = tc.foreground;
    background = tc.background;
    tc.foreground = std::nullopt;
    tc.background = std::nullopt;
}

TextColor &TextColor::operator=(const TextColor &tc) {
    foreground = tc.foreground;
    background = tc.background;
    return *this;
}

bool TextColor::operator==(const TextColor &rhs) const {
    return foreground == rhs.foreground &&
           background == rhs.background;
}

bool TextColor::operator!=(const TextColor &rhs) const {
    return !(rhs == *this);
}

}