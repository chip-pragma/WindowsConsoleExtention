#pragma once

#include <vector>
#include <cstdint>

#include "cpe/ui/BaseReader.h"
#include "MenuItem.h"

namespace cpe {

using MenuItemPair = std::pair<uint32_t, MenuItem*>;
using MenuItemVector = std::vector<MenuItemPair>;
using MenuReaderResult = ReaderResult<uint32_t>;

class MenuReader : public BaseReader<MenuReader, uint32_t> {
public:
    ~MenuReader() override;

    void setCommandItems(const MenuItemVector &itemList);

protected:
    MenuItemVector mCommandItems;

    bool onConvert(std::string &srcLine, uint32_t &convertedValue) override;
};

}




