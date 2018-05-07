#pragma once

#include "cpe/core/Color.h"
#include "cpe/tool/property/Nullable.h"

namespace cpe {

class TextChar {
public:
    TextChar() = default;

    explicit TextChar(char c);

    TextChar(char c, const Color &fore, const Color &back);

    TextChar(const TextChar &c);

    TextChar(TextChar &&c) noexcept;

    ~TextChar();

    Nullable<Color> &foreground() const;

    void foreground(const Nullable<Color> &fore);

    Nullable<Color> &background() const;

    void background(const Nullable<Color> &back);

    char getChar() const;

    void setChar(char aChar);

    TextChar &operator=(const TextChar &c);

private:
    Nullable<Color> mFore;
    Nullable<Color> mBack;
    char mChar = ' ';

};

}



