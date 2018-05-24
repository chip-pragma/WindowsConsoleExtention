#include "Menu.h"

namespace cpe {

MenuData::~MenuData() { }

const StyledBorder &MenuData::border() const {
    return mBorder;
}

StyledBorder &MenuData::border() {
    return mBorder;
}

const StyledText &MenuData::caption() const {
    return mCaption;
}

StyledText &MenuData::caption() {
    return mCaption;
}

const TextColor &MenuData::command_color() const {
    return mCommandColor;
}

TextColor &MenuData::command_color() {
    return mCommandColor;
}

void MenuData::set_items_source(const MenuItemMap &items) {
    mItems = &items;
}

Menu::~Menu() { }

void Menu::on_write(Buffer &buf) {
    using BS = BorderStyle;

    const auto &brd = data().border();
    buf.draw(brd[BS::SLT]);
    buf.draw(brd[BS::ST], 2);
    buf.draw(StyledChar(' '));

    {
        auto captionBuf = buf.extract(buf.cursor_position(), buf.get_size() - buf.cursor_position());
        captionBuf.draw_line(data().caption());
        buf.cursor_position() = Point(0, 1);
        buf.draw(brd[BS::SL], captionBuf.get_used_size().y_crd() - 1, true);
    }

    for (const auto &pair : mItems) {
        if (!pair.second->visible())
            continue;
        auto sumBuf = buf.extract(buf.cursor_position(), buf.get_size() - buf.cursor_position());
        pair.second->write(sumBuf, brd, data().command_color());
        buf.cursor_position().x_crd() = 0;
        buf.cursor_position().y_crd()++;
        buf.draw(brd[BS::SL], sumBuf.get_used_size().y_crd() - 1, true);
    }

    buf.cursor_position().x_crd() = 0;
    buf.draw(brd[BS::SLB]);
    buf.draw(brd[BS::SB], 2);
}

void Menu::on_before_run() {
    data().set_items_source(mItems);
}

}