#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "cpe/core/Exception.h"
#include "cpe/ui/BaseWriterData.h"
#include "cpe/ui/BaseWriter.h"
#include "BaseMenuItem.h"

namespace cpe {

using MenuItemMap = std::vector<std::pair<uint32_t, BaseMenuItem *>>;

class MenuData : public BaseWriterData {
public:
    ~MenuData() override;

    const StyledBorder &border() const;

    StyledBorder &border();

    const StyledText &caption() const;

    StyledText &caption();

    const TextColor &command_color() const;

    TextColor &command_color();

    template<class TItem>
    TItem &get(uint32_t itemId);

    void set_items_source(const MenuItemMap &items);

protected:
    const MenuItemMap *mItems;
    StyledBorder mBorder;
    StyledText mCaption;
    TextColor mCommandColor;
};

class Menu : public BaseWriter<MenuData> {
public:
    ~Menu() override;

    template<class TItem>
    void add_item(uint32_t itemId, TItem &item);

protected:
    MenuItemMap mItems;

    void on_write(Buffer &buf) override;

    void on_before_run() override;
};

template<class TItem>
TItem &MenuData::get(uint32_t itemId) {
    auto finded = std::find(mItems->cbegin(), mItems->cend(),
            [&] (auto& r) { return r.first == itemId; });
    if (finded == mItems->cend())
        throw Exception("Item with this ID not found");
    return static_cast<TItem &>(*finded);
}

template<class TItem>
void Menu::add_item(uint32_t itemId, TItem &item) {
    mItems.emplace_back(itemId, static_cast<BaseMenuItem *>(&item));
}

}




