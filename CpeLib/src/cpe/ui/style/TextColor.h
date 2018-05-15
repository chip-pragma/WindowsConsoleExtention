#pragma once

#include "cpe/core/draw/Color.h"
#include "cpe/tool/Nullable.h"

namespace cpe {

class TextColor {
public:
    TextColor() = default;

    TextColor(const TextColor &tc);

    TextColor(TextColor &&tc) noexcept;

    TextColor(Nullable<Color> fore, Nullable<Color> back);

    const Nullable<Color> &foreground() const;

    Nullable<Color> &foreground();

    const Nullable<Color> &background() const;

    Nullable<Color> &background();

    void set(const TextColor &tc);

    TextColor &operator=(const TextColor &tc);

private:
    Nullable<Color> mFore;
    Nullable<Color> mBack;
};

}




