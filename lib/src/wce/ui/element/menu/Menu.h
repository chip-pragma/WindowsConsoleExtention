#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <optional>

#include "wce/core/Exception.h"
#include "wce/ui/BaseWriter.h"
#include "BaseMenuItem.h"
#include "MenuReader.h"

namespace wce {

class Menu : public BaseWriter<Menu> {
public:
    StyledBorder border;
    StyledText caption;
    StyledText readerHint;
    TextColor commandColor;

    ~Menu() override;

    void assignReader(MenuReader &reader);

    template<class TItem, class ...Args>
    TItem & makeItem(std::optional<uint32_t> itemId, Args ...args);

    bool removeItem(uint32_t itemId);

    template<class TItem>
    TItem &getItem(uint32_t itemId);

protected:
    MenuReader *m_reader = nullptr;

    void onWrite(Buffer &buf) override;

    void onAfterRun() override;

private:
    using _IMenuItemPair = std::pair<std::optional<uint32_t>, IMenuItem*>;
    using _IMenuItemVector = std::vector<_IMenuItemPair>;

    _IMenuItemVector m_itemVec;
};


template<class TItem, class ...Args>
TItem & Menu::makeItem(std::optional<uint32_t> itemId, Args ...args) {
    bool anyOf = std::any_of(
        m_itemVec.cbegin(), m_itemVec.cend(),
        [&](const _IMenuItemPair &pair) {
            return itemId.has_value() && pair.first.has_value() && pair.first == itemId;
        });
    if (anyOf)
        throw Exception("ID already in use");

    auto item = new TItem(args...);
    m_itemVec.emplace_back(itemId, static_cast<IMenuItem *>(item));
    return *item;
}

template<class TItem>
TItem &Menu::getItem(uint32_t itemId) {
    // TODO что делать с nullopt ?
    auto finded = std::find(m_itemVec.cbegin(), m_itemVec.cend(),
                            [&](MenuItemPair &r) { return r.first == itemId; });
    if (finded == m_itemVec.cend())
        throw Exception("Item with this ID not found");
    return static_cast<TItem &>(*finded);
}

}




