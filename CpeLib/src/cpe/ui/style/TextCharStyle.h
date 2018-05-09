#pragma once

#include "cpe/ui/style/TextCharStyle.h"
#include "cpe/core/Color.h"
#include "cpe/tool/Nullable.h"

namespace cpe {

class TextCharStyle {
public:
    TextCharStyle() = default;

    TextCharStyle(const TextCharStyle& style);

    TextCharStyle(TextCharStyle&& style) noexcept;

    TextCharStyle(Nullable<Color> fore, Nullable<Color> back);

    const Nullable<Color> &get_foreground() const;

    Nullable<Color> &mod_foreground();

    void set_foreground(const Nullable <Color> &fore);

    const Nullable<Color> &get_background() const;

    Nullable<Color> &mod_background();

    void set_background(const Nullable <Color> &back);

    TextCharStyle &operator=(const TextCharStyle &style);

private:
    Nullable<Color> mFore;
    Nullable<Color> mBack;
};

}




