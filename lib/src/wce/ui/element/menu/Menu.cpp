#include "Menu.h"

namespace wce {

Menu::~Menu() {
    for (auto item : m_itemVec)
        delete item.second;
}

void Menu::assignReader(MenuReader &reader) {
    m_reader = &reader;
}

bool Menu::removeItem(uint32_t itemId) {
    auto find = std::find_if(
        m_itemVec.cbegin(), m_itemVec.cend(),
        [&](const _IMenuItemPair &pair) {
            return pair.first == itemId;
        });
    if (find != m_itemVec.cend()) {
        m_itemVec.erase(find);
        return true;
    }
    return false;
}

void Menu::onWrite(Buffer &buf) {
    using BS = BorderStyle;

    const auto &brd = this->border;
    buf.draw(brd[BS::SLT] + ' ');

    {
        auto captionBuf = buf.extract(buf.cursorPosition, buf.getSize() - buf.cursorPosition);
        captionBuf.drawLine(this->caption);
        buf.cursorPosition = Point(0, 1);
        buf.draw(brd[BS::SL], captionBuf.getUsedSize().y - 1, true);
    }

    for (const auto &pair : m_itemVec) {
        if (!pair.second->visible)
            continue;
        auto sumBuf = buf.extract(buf.cursorPosition, buf.getSize() - buf.cursorPosition);
        pair.second->write(sumBuf, brd, this->commandColor);
        buf.cursorPosition.x = 0;
        buf.cursorPosition.y++;
        buf.draw(brd[BS::SL], sumBuf.getUsedSize().y - 1, true);
    }

    buf.cursorPosition.x = 0;
    buf.draw(brd[BS::SLB] + ' ');

    {
        auto inputMsg = buf.extract(buf.cursorPosition, buf.getSize() - buf.cursorPosition);
        inputMsg.drawLine(this->readerHint);
    }
}

void Menu::onAfterRun() {
    if (m_reader) {
        MenuItemSet set;
        for (auto &item : m_itemVec) {
            auto comItem = dynamic_cast<MenuItem*>(item.second);
            if (comItem && item.first.has_value())
                set.emplace(item.first.value(), comItem);
        }
        m_reader->setCommandItems(set);
    }
}

}