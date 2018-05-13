#pragma once

#include "cpe/core/draw/Color.h"
#include "cpe/tool/Nullable.h"

namespace cpe {

class TextColor {
public:
    TextColor() = default;

    TextColor(const TextColor& style);

    TextColor(TextColor&& style) noexcept;

    TextColor(Nullable<Color> fore, Nullable<Color> back);

    const Nullable<Color> &foreground() const;

    Nullable<Color> &foreground();

    const Nullable<Color> &background() const;

    Nullable<Color> &background();

    TextColor &operator=(const TextColor &style);

private:
    Nullable<Color> mFore;
    Nullable<Color> mBack;
};

}




