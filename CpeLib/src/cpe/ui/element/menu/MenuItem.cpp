#include "MenuItem.h"
#include "cpe/tool/text.h"
#include "cpe/core/Exception.h"

namespace cpe {

MenuItem::MenuItem(const std::string &commands) {
    text::split(commands, mCommandList, "|");
    if (mCommandList.empty())
        throw Exception("Menu item command is not set");
}

const MenuItemCommandList & MenuItem::getCommandList() const {
    return mCommandList;
}

void MenuItem::write(cpe::Buffer &buf, const cpe::StyledBorder &sBord, const TextColor &commandColor) const {
    using BS = BorderStyle;
    buf.draw(sBord[BS::SL]);

    StyledText coms;
    coms.append(" ")
        .setColor(sBord.getColor())
        .append("[");

    auto &list = getCommandList();
    for (auto it = list.cbegin();;) {
        coms.setColor(commandColor)
            .append(*it)
            .setColor(sBord.getColor());
        if (++it != list.cend())
            coms.append("|");
        else
            break;
    }

    coms.append("]")
        .resetColor()
        .append(" ");
    buf.draw(coms);

    auto subBuf = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
    subBuf.draw(mText);
    buf.getCursorPos().getY() += subBuf.getUsedSize().getY();
}

}


