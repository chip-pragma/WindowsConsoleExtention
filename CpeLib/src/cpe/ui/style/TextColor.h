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

    const std::optional<Color> &getFore() const;

    std::optional<Color> &getFore();

    const std::optional<Color> &getBack() const;

    std::optional<Color> &getBack();

    TextColor &operator=(const TextColor &tc);

    bool operator==(const TextColor &rhs) const;

    bool operator!=(const TextColor &rhs) const;

private:
    std::optional<Color> mFore = std::nullopt;
    std::optional<Color> mBack = std::nullopt;
};

}




