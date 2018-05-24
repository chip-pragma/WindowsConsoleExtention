#pragma once

#include <optional>

#include "cpe/core/draw/Color.h"

namespace cpe {

class TextColor {
public:
    TextColor();

    TextColor(const TextColor &tc);

    TextColor(TextColor &&tc) noexcept;

    TextColor(std::optional<Color> fore, std::optional<Color> back);

    const std::optional<Color> &foreground() const;

    std::optional<Color> &foreground();

    const std::optional<Color> &background() const;

    std::optional<Color> &background();

    TextColor &operator=(const TextColor &tc);

private:
    std::optional<Color> mFore = std::nullopt;
    std::optional<Color> mBack = std::nullopt;
};

}




