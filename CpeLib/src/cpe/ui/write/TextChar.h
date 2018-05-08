#pragma once

#include "cpe/core/Color.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"

namespace cpe {

class TextChar {
public:
    TextChar() = default;

    explicit TextChar(char c);

    TextChar(char c, const TextCharStyle &style);

    TextChar(const TextChar &c);

    TextChar(TextChar &&c) noexcept;

    ~TextChar();

    TextCharStyle &style();

    void style(const TextCharStyle &style);

    char getAChar() const;

    void setAChar(char aChar);

    char getChar() const;

    void setChar(char aChar);

    TextChar &operator=(const TextChar &c);

private:
    TextCharStyle mStyle;
    char mChar = ' ';

};

}



