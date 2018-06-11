#include "Menu.h"

namespace cpe {

Menu::~Menu() {
    for (auto item : mItems)
        delete item.second;
    delete mReader;
}

const StyledBorder &Menu::getBorder() const {
    return mBorder;
}

StyledBorder &Menu::getBorder() {
    return mBorder;
}

const StyledText &Menu::getCaption() const {
    return mCaption;
}

StyledText &Menu::getCaption() {
    return mCaption;
}

const StyledText &Menu::getReaderHint() const {
    return mReaderHint;
}

StyledText &Menu::getReaderHint() {
    return mReaderHint;
}

const TextColor &Menu::getCommandColor() const {
    return mCommandColor;
}

TextColor &Menu::getCommandColor() {
    return mCommandColor;
}

void Menu::assignReader(MenuReader *reader) {
    mReader = reader;
}

void Menu::removeItem(uint32_t itemId) {
    // TODO удаление компонента
}

void Menu::onWrite(Buffer &buf) {
    using BS = BorderStyle;

    const auto &brd = this->getBorder();
    buf.draw(brd[BS::SLT] + ' ');

    {
        auto captionBuf = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        captionBuf.drawLine(this->getCaption());
        buf.getCursorPos() = Point(0, 1);
        buf.draw(brd[BS::SL], captionBuf.getUsedSize().getY() - 1, true);
    }

    for (const auto &pair : mItems) {
        if (!pair.second->getVisible())
            continue;
        auto sumBuf = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        pair.second->write(sumBuf, brd, this->getCommandColor());
        buf.getCursorPos().getX() = 0;
        buf.getCursorPos().getY()++;
        buf.draw(brd[BS::SL], sumBuf.getUsedSize().getY() - 1, true);
    }

    buf.getCursorPos().getX() = 0;
    buf.draw(brd[BS::SLB] + ' ');

    {
        auto inputMsg = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        inputMsg.drawLine(this->getReaderHint());
    }
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