#pragma once

#include <cstdint>

#include "BaseMenuItem.h"

namespace cpe {

using MenuItemCommandList = std::vector<std::string>;

class MenuItem : public BaseMenuItem {
public:
    explicit MenuItem(const std::string &commands);

    const MenuItemCommandList & getCommandList() const;

    void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const override;

protected:
    MenuItemCommandList mCommandList;
};

}




