#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "cpe/core/Exception.h"
#include "cpe/ui/BaseWriter.h"
#include "BaseMenuItem.h"
#include "MenuReader.h"

namespace wce {

class Menu : public BaseWriter<Menu> {
public:
    ~Menu() override;

    const StyledBorder &getBorder() const;

    StyledBorder &getBorderRef();

    const StyledText &getCaption() const;

    StyledText &getCaptionRef();

    const StyledText &getReaderHint() const;

    StyledText &getReaderHintRef();

    const TextColor &getCommandColor() const;

    TextColor &getCommandColorRef();

    void assignReader(MenuReader &reader);

    template<class TItem, class ...Args>
    TItem & makeItem(uint32_t itemId, Args ...args);

    bool removeItem(uint32_t itemId);

    template<class TItem>
    TItem &getItem(uint32_t itemId);

protected:
    MenuReader *mReader = nullptr;
    StyledBorder mBorder;
    StyledText mCaption;
    StyledText mReaderHint;
    TextColor mCommandColor;

    void onWrite(Buffer &buf) override;

    void onAfterRun() override;

private:
    using _IMenuItemPair = std::pair<uint32_t, IMenuItem*>;
    using _IMenuItemVector = std::vector<_IMenuItemPair>;

    _IMenuItemVector mItemVec;
};


template<class TItem, class ...Args>
TItem & Menu::makeItem(uint32_t itemId, Args ...args) {
    bool anyOf = std::any_of(
        mItemVec.cbegin(), mItemVec.cend(),
        [&](const _IMenuItemPair &pair) {
            return pair.first == itemId;
        });
    if (anyOf)
        throw Exception("ID already in use");

    auto item = new TItem(args...);
    mItemVec.emplace_back(itemId, static_cast<IMenuItem *>(item));
    return *item;
}

template<class TItem>
TItem &Menu::getItem(uint32_t itemId) {
    auto finded = std::find(mItemVec.cbegin(), mItemVec.cend(),
                            [&](MenuItemPair &r) { return r.first == itemId; });
    if (finded == mItemVec.cend())
        throw Exception("Item with this ID not found");
    return static_cast<TItem &>(*finded);
}

}




