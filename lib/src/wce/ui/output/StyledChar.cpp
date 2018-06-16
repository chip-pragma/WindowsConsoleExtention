#include "StyledChar.h"
#include "Buffer.h"

#include <utility>

namespace wce {

StyledChar::StyledChar() { }

StyledChar::StyledChar(char c)
    : character(c) { }

StyledChar::StyledChar(char c, const TextColor &color)
    : character(c), color(color) { }

StyledChar::StyledChar(const StyledChar &sch) {
    character = sch.character;
    color = sch.color;
}

StyledChar::StyledChar(StyledChar &&sch) noexcept {
    character = sch.character;
    color = sch.color;
}

StyledChar &StyledChar::operator=(const StyledChar &sch) {
    character = sch.character;
    color = sch.color;
    return *this;
}

}



