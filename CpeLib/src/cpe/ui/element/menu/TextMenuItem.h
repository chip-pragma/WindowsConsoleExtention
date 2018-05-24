#pragma once

#include <cstdint>

#include "IMenuItem.h"

namespace cpe {

class TextMenuItem : public IMenuItem {
public:
    explicit TextMenuItem(uint32_t itemId);

    TextMenuItem(uint32_t itemId, const std::string &text);

    uint32_t item_id() const;

    const std::string &text() const;

    std::string &text();

    void write(Buffer &buf, const StyledBorder &sBord) const override;

protected:
    uint32_t mItemId;
    std::string mText;
};

}




