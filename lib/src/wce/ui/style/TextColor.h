#pragma once

#include <optional>

#include "wce/core/ColorIndex.h"

namespace wce {

class TextColor {
public:
    std::optional<ColorIndex> foreground = std::nullopt;
    std::optional<ColorIndex> background = std::nullopt;

    TextColor();

    TextColor(const TextColor &tc);

    TextColor(TextColor &&tc) noexcept;

    TextColor(std::optional<ColorIndex> fore, std::optional<ColorIndex> back);

    TextColor &operator=(const TextColor &tc);

    bool operator==(const TextColor &rhs) const;

    bool operator!=(const TextColor &rhs) const;
};

}




