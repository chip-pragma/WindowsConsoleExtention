#pragma once

#include <cstdint>

#include "BaseCommandMenuItem.h"

namespace cpe {

class MenuItem : public BaseCommandMenuItem {
public:
    explicit MenuItem(const std::string &commands);

    const StyledText &getText() const;

    StyledText &getText();

    void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const override;

protected:
    StyledText mText;
};

}




