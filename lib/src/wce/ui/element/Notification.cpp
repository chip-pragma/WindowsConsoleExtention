#include "Notification.h"
#include "wce/tool/Encoder.h"

namespace wce {

void Notification::onWrite(Buffer &cvs) {
    using BS = BorderStyle;

    Point innerSize = cvs.getSize() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.getLocation() != Point::PL_SECTOR_I) {
        cvs.draw(StyledText().append("[NO PLACE]"));
        return;
    }

    Buffer text = cvs.extract(margin / 2 + Point(1, 1), textBlockSize, false);
    text.draw(this->text);
    Point textBlockUsedSize = text.getUsedSize() + margin;

    auto &brd = this->border;

    cvs.draw(brd[BS::SLT]);
    cvs.draw(brd[BS::ST], textBlockUsedSize.x, false);
    cvs.draw(brd[BS::SRT]);

    cvs.cursorPosition = Point(0, 1);
    cvs.draw(brd[BS::SL], textBlockUsedSize.y, true);
    cvs.cursorPosition = Point(textBlockUsedSize.x + 1, 1);
    cvs.draw(brd[BS::SR], textBlockUsedSize.y, true);

    cvs.cursorPosition = Point(0, textBlockUsedSize.y + 1);
    cvs.draw(brd[BS::SLB]);
    cvs.draw(brd[BS::SB], textBlockUsedSize.x, false);
    cvs.draw(brd[BS::SRB]);

    // Open
    cvs.cursorPosition = Point(1, 0);

    if (this->icon.has_value()) {
        cvs.cursorPosition.x++;
        cvs.draw(StyledChar('[', brd.color));
        cvs.draw(this->icon.value());
        cvs.draw(StyledChar(']', brd.color));
    }

    if (this->caption.has_value()
        && (cvs.cursorPosition.x + 3 < cvs.getSize().x - 2)) {
        cvs.cursorPosition.x++;
        cvs.draw(StyledChar('[', brd.color));
        auto captionWidth = cvs.getSize().x - cvs.cursorPosition.x - 3;
        auto caption = cvs.extract(cvs.cursorPosition,
                                   Point(captionWidth, 1));
        caption.draw(this->caption.value());
        cvs.cursorPosition.x += captionWidth;
        cvs.draw(StyledChar(']', brd.color));
    }
}

}



