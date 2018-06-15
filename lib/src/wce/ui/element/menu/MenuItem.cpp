#include "MenuItem.h"
#include "wce/tool/text.h"
#include "wce/core/Exception.h"

namespace wce {

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
            .setColor(sBord.getColor());
        if (++it != list.cend())
            coms.append(",");
        else
            break;
    }

    coms.resetColor()
        .append(" ");
    buf.draw(coms);

    auto subBuf = buf.extract(buf.getCursorPosRef(), buf.getSize() - buf.getCursorPosRef());
    subBuf.draw(mText);
    buf.getCursorPosRef().getYRef() += subBuf.getUsedSize().getYRef();
}

}


