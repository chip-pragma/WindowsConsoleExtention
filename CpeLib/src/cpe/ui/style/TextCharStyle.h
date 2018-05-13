#pragma once

#include "cpe/ui/style/TextCharStyle.h"
#include "cpe/core/draw/Color.h"
#include "cpe/tool/Nullable.h"

namespace cpe {

class TextCharStyle {
public:
    TextCharStyle() = default;

    TextCharStyle(const TextCharStyle& style);

    TextCharStyle(TextCharStyle&& style) noexcept;

    TextCharStyle(Nullable<Color> fore, Nullable<Color> back);

    const Nullable<Color> &foreground() const;

    Nullable<Color> &foreground();

    const Nullable<Color> &background() const;

    Nullable<Color> &background();

    TextCharStyle &operator=(const TextCharStyle &style);

private:
    Nullable<Color> mFore;
    Nullable<Color> mBack;
};

}




