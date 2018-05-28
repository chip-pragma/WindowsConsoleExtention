#pragma once

#include <cstdint>

#include "BaseMenuItem.h"

namespace cpe {

using MenuItemPair = std::pair<uint32_t, BaseMenuItem *>;
using MenuItemMap = std::vector<MenuItemPair>;

class BaseSetItemsSource {
public:
    virtual ~BaseSetItemsSource() {}

    virtual void set_items_source(MenuItemMap &items);

protected:
    MenuItemMap *mItems = nullptr;
};

}




