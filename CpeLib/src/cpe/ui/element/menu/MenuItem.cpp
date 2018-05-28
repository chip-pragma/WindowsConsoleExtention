#include "MenuItem.h"

namespace cpe {

MenuItem::MenuItem(const std::string &commands)
    : BaseCommandMenuItem(commands) { }

const StyledText &MenuItem::getText() const {
    return mText;
}

StyledText &MenuItem::getText() {
    return mText;
}

void MenuItem::write(cpe::Buffer &buf, const cpe::StyledBorder &sBord, const TextColor &commandColor) const {
    using BS = BorderStyle;
    buf.draw(sBord[BS::SL]);

    StyledText coms;
    coms.append(" ")
        .color(sBord.color())
        .append("[");

    auto &list = getCommandList();
    for (auto it = list.cbegin();;) {
        coms.color(commandColor)
            .append(*it)
            .color(sBord.color());
        if (++it != list.cend())
            coms.append("|");
        else
            break;
    }

    coms.append("]")
        .reset_color()
        .append(" ");
    buf.draw(coms);

    auto subBuf = buf.extract(buf.cursor_position(), buf.get_size() - buf.cursor_position());
    subBuf.draw(mText);
    buf.cursor_position().y_crd() += subBuf.get_used_size().y_crd();
}

}


