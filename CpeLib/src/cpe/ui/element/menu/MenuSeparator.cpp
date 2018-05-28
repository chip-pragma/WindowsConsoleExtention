#include "MenuSeparator.h"

namespace cpe {

void MenuSeparator::write(cpe::Buffer &buf,
                          const cpe::StyledBorder &sBord,
                          const cpe::TextColor &commandColor) const {
    using BS = BorderStyle;
    buf.draw(sBord[BS::SLH]);
    buf.draw(sBord[BS::SH], 2);
    buf.draw(' ');

    // FIXME не корректный расчет используемой ширины подбуффера
    {
        auto textBuf = buf.extract(buf.getCursorPos(), buf.getSize() - buf.getCursorPos());
        textBuf.drawLine(getText());
        buf.getCursorPos() = Point(0, 1);
        buf.draw(sBord[BS::SL], textBuf.getUsedSize().getY() - 1, true);
    }
}

}


