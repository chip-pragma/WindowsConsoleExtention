#pragma once

#include "cpe/core/Color.h"
#include "cpe/tool/property/Nullable.h"

namespace cpe {

class TextCharStyle {
public:
    TextCharStyle() = default;

    TextCharStyle(Nullable<Color> fore, Nullable<Color> back);

    Nullable<Color> &foreground() const;

    void foreground(const Nullable<Color> &fore);

    Nullable<Color> &background() const;

    void background(const Nullable<Color> &back);

    TextCharStyle &operator=(const TextCharStyle &style);

private:
    Nullable<Color> mFore;
    Nullable<Color> mBack;
};

}




