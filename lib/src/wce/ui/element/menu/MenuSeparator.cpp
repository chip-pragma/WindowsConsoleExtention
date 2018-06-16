#include "MenuSeparator.h"

namespace wce {

MenuSeparator::~MenuSeparator() {

}

void MenuSeparator::write(Buffer &buf,
                          const StyledBorder &sBord,
                          const TextColor &commandColor) const {
    using BS = BorderStyle;
    buf.draw(sBord[BS::SLH] + ' ');

    {
        auto textBuf = buf.extract(buf.cursorPosition, buf.getSize() - buf.cursorPosition);
        textBuf.drawLine(text);
        buf.cursorPosition = Point(0, 1);
        buf.draw(sBord[BS::SL], textBuf.getUsedSize().y - 1, true);
    }
}

}


