#pragma once

#include <vector>

#include "cpe/ui/BaseReader.h"
#include "MenuItem.h"

namespace cpe {

using MenuItemPair = std::pair<uint32_t, MenuItem*>;
using MenuItemVector = std::vector<MenuItemPair>;

class MenuReader : public BaseReader<uint32_t> {
public:
    ~MenuReader() override;

    void setCommandItems(const MenuItemVector &itemList);

protected:
    MenuItemVector mCommandItems;

    bool onConvert(std::string &srcLine, uint32_t &convertedValue) override;
};

}




