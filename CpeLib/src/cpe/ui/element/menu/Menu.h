#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "cpe/core/Exception.h"
#include "cpe/ui/BaseWriter.h"
#include "BaseMenuItem.h"
#include "MenuReader.h"

namespace cpe {

using IMenuItemPair = std::pair<uint32_t, IMenuItem*>;
using IMenuItemVector = std::vector<IMenuItemPair>;

class Menu : public BaseWriter<Menu> {
public:
    ~Menu() override;

    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    const StyledText &getCaption() const;

    StyledText &getCaption();

    const StyledText &getReaderHint() const;

    StyledText &getReaderHint();

    const TextColor &getCommandColor() const;

    TextColor &getCommandColor();

    void assignReader(MenuReader *reader);

    template<class TItem>
    void addItem(uint32_t itemId, TItem &item);

    void removeItem(uint32_t itemId);

    template<class TItem>
    TItem &getItem(uint32_t itemId);

protected:
    IMenuItemVector mItems;
    MenuReader *mReader = nullptr;
    StyledBorder mBorder;
    StyledText mCaption;
    StyledText mReaderHint;
    TextColor mCommandColor;

    void onWrite(Buffer &buf) override;

protected:

    void onAfterRun() override;
};

template<class TItem>
void Menu::addItem(uint32_t itemId, TItem &item) {
    // TODO уникальный ID
    mItems.emplace_back(itemId, static_cast<IMenuItem *>(&item));
}

template<class TItem>
TItem &Menu::getItem(uint32_t itemId) {
    auto finded = std::find(mItems.cbegin(), mItems.cend(),
                            [&](MenuItemPair &r) { return r.first == itemId; });
    if (finded == mItems.cend())
        throw Exception("Item with this ID not found");
    return static_cast<TItem &>(*finded);
}

}




