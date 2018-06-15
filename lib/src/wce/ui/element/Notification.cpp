#include "Notification.h"
#include "wce/tool/Encoder.h"

namespace wce {

const StyledBorder &Notification::getBorder() const {
    return mBorder;
}

StyledBorder &Notification::getBorderRef() {
    return mBorder;
}

const std::optional<StyledText> &Notification::getCaption() const {
    return mCaption;
}

std::optional<StyledText> &Notification::getCaptionRef() {
    return mCaption;
}

const StyledText &Notification::getText() const {
    return mText;
}

StyledText &Notification::getTextRef() {
    return mText;
}

const std::optional<StyledChar> &Notification::getIcon() const {
    return mIcon;
}

std::optional<StyledChar> &Notification::getIconRef() {
    return mIcon;
}

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
    text.draw(this->getTextRef());
    Point textBlockUsedSize = text.getUsedSize() + margin;

    auto &brd = this->getBorderRef();

    cvs.draw(brd[BS::SLT]);
    cvs.draw(brd[BS::ST], textBlockUsedSize.getXRef(), false);
    cvs.draw(brd[BS::SRT]);

    cvs.getCursorPosRef() = Point(0, 1);
    cvs.draw(brd[BS::SL], textBlockUsedSize.getYRef(), true);
    cvs.getCursorPosRef() = Point(textBlockUsedSize.getXRef() + 1, 1);
    cvs.draw(brd[BS::SR], textBlockUsedSize.getYRef(), true);

    cvs.getCursorPosRef() = Point(0, textBlockUsedSize.getYRef() + 1);
    cvs.draw(brd[BS::SLB]);
    cvs.draw(brd[BS::SB], textBlockUsedSize.getXRef(), false);
    cvs.draw(brd[BS::SRB]);

    // Open
    cvs.getCursorPosRef() = Point(1, 0);

    if (this->getIconRef().has_value()) {
        cvs.getCursorPosRef().getXRef()++;
        cvs.draw(StyledChar('[', brd.getColorRef()));
        cvs.draw(this->getIconRef().value());
        cvs.draw(StyledChar(']', brd.getColorRef()));
    }

    if (this->getCaptionRef().has_value()
        && (cvs.getCursorPosRef().getXRef() + 3 < cvs.getSize().getX() - 2)) {
        cvs.getCursorPosRef().getXRef()++;
        cvs.draw(StyledChar('[', brd.getColorRef()));
        auto captionWidth = cvs.getSize().getX() - cvs.getCursorPosRef().getXRef() - 3;
        auto caption = cvs.extract(cvs.getCursorPosRef(),
                                   Point(captionWidth, 1));
        caption.draw(this->getCaptionRef().value());
        cvs.getCursorPosRef().getXRef() += captionWidth;
        cvs.draw(StyledChar(']', brd.getColorRef()));
    }
}

}



