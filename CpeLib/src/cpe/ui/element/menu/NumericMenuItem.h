#pragma once

#include <cstdint>

#include "BaseMenuItem.h"

namespace cpe {

class NumericMenuItem : public BaseMenuItem {
public:
    NumericMenuItem() = default;

    explicit NumericMenuItem(uint32_t index);

    NumericMenuItem(uint32_t index, const std::string &text);

    const uint32_t& index() const;

    uint32_t& index();

    const StyledText &text() const;

    StyledText &text();

    void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const override;

    std::string get_command() const override;

protected:
    uint32_t mIndex;
    StyledText mText;
};

}




