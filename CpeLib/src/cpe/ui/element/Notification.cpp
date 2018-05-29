#include "cpe/tool/Encoder.h"
#include "cpe/ui/IWriter.h"
#include "Notification.h"

namespace cpe {

//region [ NotificationData ]

NotificationData::NotificationData() { }

const StyledBorder &NotificationData::getBorder() const {
    return mBorder;
}

StyledBorder &NotificationData::getBorder() {
    return mBorder;
}

const std::optional<StyledText> &NotificationData::getCaption() const {
    return mCaption;
}

std::optional<StyledText> &NotificationData::getCaption() {
    return mCaption;
}

const StyledText &NotificationData::getText() const {
    return mText;
}

StyledText &NotificationData::getText() {
    return mText;
}

const std::optional<StyledChar> &NotificationData::getIcon() const {
    return mIcon;
}

std::optional<StyledChar> &NotificationData::getIcon() {
    return mIcon;
}

bool NotificationData::getWait() const {
    return mWait;
}

void NotificationData::setWait(bool wait) {
    mWait = wait;
}

//endregion

void Notification::outputTo(std::ostream &outStream) {
    BaseWriter::outputTo(outStream);
    if (getData().getWait())
        term::callPause();
}

void Notification::onWrite(Buffer &cvs) {
    using BS = BorderStyle;

    Point innerSize = cvs.getSize() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.dimension() != Point::DIM_SECTOR_I) {
        cvs.draw(StyledText().append("[NO PLACE]"));
        return;
    }

    Buffer text = cvs.extract(margin / 2 + Point(1, 1), textBlockSize, false);
    text.draw(getData().getText());
    Point textBlockUsedSize = text.getUsedSize() + margin;

    auto &brd = getData().getBorder();

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

    if (getData().getIcon().has_value()) {
        cvs.getCursorPos().getX()++;
        cvs.draw(StyledChar('[', brd.getColor()));
        cvs.draw(getData().getIcon().value());
        cvs.draw(StyledChar(']', brd.getColor()));
    }

    if (getData().getCaption().has_value()
        && (cvs.getCursorPos().getX() + 3 < cvs.getSize().getX() - 2)) {
        cvs.getCursorPos().getX()++;
        cvs.draw(StyledChar('[', brd.getColor()));
        auto captionWidth = cvs.getSize().getX() - cvs.getCursorPos().getX() - 3;
        auto caption = cvs.extract(cvs.getCursorPos(),
                                   Point(captionWidth, 1));
        caption.draw(getData().getCaption().value());
        cvs.getCursorPos().getX() += captionWidth;
        cvs.draw(StyledChar(']', brd.getColor()));
    }
}

}



