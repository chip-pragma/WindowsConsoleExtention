#include "Menu.h"

namespace cpe {

MenuData::~MenuData() { }

const StyledBorder &MenuData::getBorder() const {
    return mBorder;
}

StyledBorder &MenuData::getBorder() {
    return mBorder;
}

const StyledText &MenuData::getCaption() const {
    return mCaption;
}

StyledText &MenuData::getCaption() {
    return mCaption;
}

const StyledText &MenuData::getReaderHint() const {
    return mReaderHint;
}

StyledText &MenuData::getReaderHint() {
    return mReaderHint;
}

const TextColor &MenuData::getCommandColor() const {
    return mCommandColor;
}

TextColor &MenuData::getCommandColor() {
    return mCommandColor;
}

void MenuData::setItems(IMenuItemVector &items) {
    mItems = &items;
}

Menu::~Menu() { }

void Menu::assignReader(MenuReader &reader) {
    mReader = &reader;
}

void Menu::onWrite(Buffer &buf) {
    using BS = BorderStyle;

    const auto &brd = getData().getBorder();
    buf.draw(brd[BS::SLT]);
    buf.draw(brd[BS::ST], 2);
    buf.draw(StyledChar(' '));

    {
        auto captionBuf = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        captionBuf.drawLine(getData().getCaption());
        buf.getCursorPos() = Point(0, 1);
        buf.draw(brd[BS::SL], captionBuf.getUsedSize().getY() - 1, true);
    }

    for (const auto &pair : mItems) {
        if (!pair.second->getVisible())
            continue;
        auto sumBuf = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        pair.second->write(sumBuf, brd, getData().getCommandColor());
        buf.getCursorPos().getX() = 0;
        buf.getCursorPos().getY()++;
        buf.draw(brd[BS::SL], sumBuf.getUsedSize().getY() - 1, true);
    }

    buf.getCursorPos().getX() = 0;
    buf.draw(brd[BS::SLB]);
    buf.draw(brd[BS::SB], 2);
    buf.draw(StyledChar(' '));

    {
        auto inputMsg = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        inputMsg.drawLine(getData().getReaderHint());
    }
}

void Menu::onBeforeRun() {
    getData().setItems(mItems);
}

void Menu::onAfterRun() {
    if (mReader) {
        MenuItemVector vec;
        for (auto& item : mItems) {
            auto comItem = dynamic_cast<MenuItem*>(item.second);
            if (comItem)
                vec.emplace_back(item.first, comItem);
        }
        mReader->setCommandItems(vec);
    }
}

}