#pragma once

#include <vector>

#include "cpe/ui/BaseReader.h"
#include "BaseCommandMenuItem.h"

namespace cpe {

using MenuCommandItemPair = std::pair<uint32_t, BaseCommandMenuItem*>;
using MenuCommandItemVector = std::vector<MenuCommandItemPair>;

class MenuReader : public BaseReader<uint32_t> {
public:
    ~MenuReader() override;

    void setCommandItems(const MenuCommandItemVector &itemList);

protected:
    MenuCommandItemVector mCommandItems;

    bool onConvert(std::string &srcLine, uint32_t &convertedValue) override;
};

}




