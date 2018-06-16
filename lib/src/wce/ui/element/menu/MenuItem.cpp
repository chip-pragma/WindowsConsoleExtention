#include "MenuItem.h"
#include "wce/tool/text.h"
#include "wce/core/Exception.h"

namespace wce {

MenuItem::~MenuItem() {

}

MenuItem::MenuItem(const std::string &commands) {
    text::split(commands, mCommandList, "|");
    if (mCommandList.empty())
        throw Exception("Menu item getCommand is not set");
}

const MenuItemCommandList & MenuItem::getCommandList() const {
    return mCommandList;
}

void MenuItem::write(wce::Buffer &buf, const wce::StyledBorder &sBord, const TextColor &commandColor) const {
    using BS = BorderStyle;
    buf.draw(sBord[BS::SL]);

    StyledText coms;
    coms.append(" ");

    auto &list = getCommandList();
    for (auto it = list.cbegin();;) {
        coms.setColor(commandColor)
            .append(*it)
            .setColor(sBord.color);
        if (++it != list.cend())
            coms.append(",");
        else
            break;
    }

    coms.resetColor()
        .append(" ");
    buf.draw(coms);

    auto subBuf = buf.extract(buf.cursorPosition, buf.getSize() - buf.cursorPosition);
    subBuf.draw(text);
    buf.cursorPosition.y += subBuf.getUsedSize().y;
}

}


