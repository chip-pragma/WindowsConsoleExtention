#include "MenuSeparator.h"

namespace cpe {

void MenuSeparator::write(Buffer &buf,
                          const StyledBorder &sBord,
                          const TextColor &commandColor) const {
    using BS = BorderStyle;
    buf.draw(sBord[BS::SLH] + ' ');

    {
        auto textBuf = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        textBuf.drawLine(getText());
        buf.getCursorPos() = Point(0, 1);
        buf.draw(sBord[BS::SL], textBuf.getUsedSize().getY() - 1, true);
    }
}

}

