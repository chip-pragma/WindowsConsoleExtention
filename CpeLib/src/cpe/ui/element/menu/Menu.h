#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "cpe/core/Exception.h"
#include "cpe/ui/BaseWriterData.h"
#include "cpe/ui/BaseWriter.h"
#include "BaseCommandMenuItem.h"
#include "MenuReader.h"

namespace cpe {

using MenuItemPair = std::pair<uint32_t, IMenuItem*>;
using MenuItemVector = std::vector<MenuItemPair>;

class MenuData : public BaseWriterData {
public:
    ~MenuData() override;

    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    const StyledText &getCaption() const;

    StyledText &getCaption();

    const StyledText &getReaderHint() const;

    StyledText &getReaderHint();

    const TextColor &getCommandColor() const;

    TextColor &getCommandColor();

    template<class TItem>
    TItem &getItem(uint32_t itemId);

    void setItems(MenuItemVector& items);

protected:
    StyledBorder mBorder;
    StyledText mCaption;
    StyledText mReaderHint;
    TextColor mCommandColor;
    MenuItemVector* mItems;
};

class Menu : public BaseWriter<MenuData> {
public:
    ~Menu() override;

    void assignReader(MenuReader &reader);

    template<class TItem>
    void addItem(uint32_t itemId, TItem &item);

protected:
    MenuItemVector mItems;
    MenuReader *mReader = nullptr;

    void onWrite(Buffer &buf) override;

    void onBeforeRun() override;

    void onAfterRun() override;
};

template<class TItem>
TItem &MenuData::getItem(uint32_t itemId) {
    auto finded = std::find(mItems->cbegin(), mItems->cend(),
                            [&](MenuItemPair &r) { return r.first == itemId; });
    if (finded == mItems->cend())
        throw Exception("Item with this ID not found");
    return static_cast<TItem &>(*finded);
}

template<class TItem>
void Menu::addItem(uint32_t itemId, TItem &item) {
    mItems.emplace_back(itemId, static_cast<IMenuItem *>(&item));
}

}




