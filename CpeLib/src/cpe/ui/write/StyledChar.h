#pragma once

#include "cpe/core/Color.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"

namespace cpe {

class StyledChar {
public:
    StyledChar() = default;

    explicit StyledChar(char c);

    StyledChar(char c, const TextCharStyle &style);

    StyledChar(const StyledChar &c);

    StyledChar(StyledChar &&c) noexcept;

    ~StyledChar();

    const TextCharStyle &style() const;

    TextCharStyle &style();

    void style(const TextCharStyle &style);

    char character() const;

    void character(char aChar);

    StyledChar &operator=(const StyledChar &c);

private:
    TextCharStyle mStyle;
    char mChar = ' ';

};

}



