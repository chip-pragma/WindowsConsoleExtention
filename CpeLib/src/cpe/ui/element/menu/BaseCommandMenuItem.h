#pragma once

#include "IMenuItem.h"

namespace cpe {

using MenuItemCommandList = std::vector<std::string>;

class BaseCommandMenuItem : public IMenuItem {
public:
    explicit BaseCommandMenuItem(const std::string &commands);

    const bool &getVisible() const override;

    bool &getVisible() override;

    const MenuItemCommandList & getCommandList() const;

protected:
    bool mVisible = true;
    MenuItemCommandList mCommandList;
};

}


