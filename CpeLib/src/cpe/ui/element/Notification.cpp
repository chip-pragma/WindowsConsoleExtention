#include "Notification.h"
#include "cpe/tool/Encoder.h"

namespace cpe {

const StyledBorder &Notification::getBorder() const {
    return mBorder;
}

StyledBorder &Notification::refBorder() {
    return mBorder;
}

const std::optional<StyledText> &Notification::getCaption() const {
    return mCaption;
}

std::optional<StyledText> &Notification::getCaption() {
    return mCaption;
}

const StyledText &Notification::getText() const {
    return mText;
}

StyledText &Notification::refText() {
    return mText;
}

const std::optional<StyledChar> &Notification::getIcon() const {
    return mIcon;
}

std::optional<StyledChar> &Notification::getIcon() {
    return mIcon;
}

void Notification::onWrite(Buffer &cvs) {
    using BS = BorderStyle;

    Point innerSize = cvs.getSize() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.calcLocation() != Point::PL_SECTOR_I) {
        cvs.draw(StyledText().append("[NO PLACE]"));
        return;
    }

    Buffer text = cvs.extract(margin / 2 + Point(1, 1), textBlockSize, false);
    text.draw(this->refText());
    Point textBlockUsedSize = text.getUsedSize() + margin;

    auto &brd = this->refBorder();

    cvs.draw(brd[BS::SLT]);
    cvs.draw(brd[BS::ST], textBlockUsedSize.getX(), false);
    cvs.draw(brd[BS::SRT]);

    cvs.getCursorPos() = Point(0, 1);
    cvs.draw(brd[BS::SL], textBlockUsedSize.getY(), true);
    cvs.getCursorPos() = Point(textBlockUsedSize.getX() + 1, 1);
    cvs.draw(brd[BS::SR], textBlockUsedSize.getY(), true);

    cvs.getCursorPos() = Point(0, textBlockUsedSize.getY() + 1);
    cvs.draw(brd[BS::SLB]);
    cvs.draw(brd[BS::SB], textBlockUsedSize.getX(), false);
    cvs.draw(brd[BS::SRB]);

    // Open
    cvs.getCursorPos() = Point(1, 0);

    if (this->getIcon().has_value()) {
        cvs.getCursorPos().getX()++;
        cvs.draw(StyledChar('[', brd.refColor()));
        cvs.draw(this->getIcon().value());
        cvs.draw(StyledChar(']', brd.refColor()));
    }

    if (this->getCaption().has_value()
        && (cvs.getCursorPos().getX() + 3 < cvs.getSize().getX() - 2)) {
        cvs.getCursorPos().getX()++;
        cvs.draw(StyledChar('[', brd.refColor()));
        auto captionWidth = cvs.getSize().getX() - cvs.getCursorPos().getX() - 3;
        auto caption = cvs.extract(cvs.getCursorPos(),
                                   Point(captionWidth, 1));
        caption.draw(this->getCaption().value());
        cvs.getCursorPos().getX() += captionWidth;
        cvs.draw(StyledChar(']', brd.refColor()));
    }
}

}



