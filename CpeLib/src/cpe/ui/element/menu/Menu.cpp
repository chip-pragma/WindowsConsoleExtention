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

void MenuData::setItems(MenuItemVector &items) {
    mItems = &items;
}

Menu::~Menu() { }

void Menu::assignReader(MenuReader &reader) {
    mReader = &reader;
}

void Menu::onWrite(Buffer &buf) {
    using BS = BorderStyle;

    const auto &brd = data().getBorder();
    buf.draw(brd[BS::SLT]);
    buf.draw(brd[BS::ST], 2);
    buf.draw(StyledChar(' '));

    {
        auto captionBuf = buf.extract(buf.cursor_position(), buf.get_size() - buf.cursor_position());
        captionBuf.draw_line(data().getCaption());
        buf.cursor_position() = Point(0, 1);
        buf.draw(brd[BS::SL], captionBuf.get_used_size().y_crd() - 1, true);
    }

    for (const auto &pair : mItems) {
        if (!pair.second->getVisible())
            continue;
        auto sumBuf = buf.extract(buf.cursor_position(), buf.get_size() - buf.cursor_position());
        pair.second->write(sumBuf, brd, data().getCommandColor());
        buf.cursor_position().x_crd() = 0;
        buf.cursor_position().y_crd()++;
        buf.draw(brd[BS::SL], sumBuf.get_used_size().y_crd() - 1, true);
    }

    buf.cursor_position().x_crd() = 0;
    buf.draw(brd[BS::SLB]);
    buf.draw(brd[BS::SB], 2);
    buf.draw(StyledChar(' '));

    {
        auto inputMsg = buf.extract(buf.cursor_position(), buf.get_size() - buf.cursor_position());
        inputMsg.draw_line(data().getReaderHint());
    }
}

void Menu::onBeforeRun() {
    data().setItems(mItems);
}

void Menu::onAfterRun() {
    if (mReader) {
        MenuCommandItemVector vec;
        for (auto& item : mItems) {
            auto comItem = dynamic_cast<BaseCommandMenuItem*>(item.second);
            if (comItem)
                vec.emplace_back(item.first, comItem);
        }
        mReader->setCommandItems(vec);
    }
}

}