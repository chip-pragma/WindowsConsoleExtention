#include "cpe/tool/Encoder.h"
#include "cpe/ui/IWriter.h"
#include "Notification.h"

namespace cpe {

//region [ NotificationData ]

NotificationData::NotificationData() { }

const StyledBorder &NotificationData::border() const {
    return mBorder;
}

StyledBorder &NotificationData::border() {
    return mBorder;
}

const std::optional<StyledText> &NotificationData::caption() const {
    return mCaption;
}

std::optional<StyledText> &NotificationData::caption() {
    return mCaption;
}

const StyledText &NotificationData::text() const {
    return mText;
}

StyledText &NotificationData::text() {
    return mText;
}

const std::optional<StyledChar> &NotificationData::icon() const {
    return mIcon;
}

std::optional<StyledChar> &NotificationData::icon() {
    return mIcon;
}

bool NotificationData::is_wait() const {
    return mWait;
}

void NotificationData::wait(bool wait) {
    mWait = wait;
}

//endregion

void Notification::output_to(std::ostream &outStream) {
    BaseWriter::output_to(outStream);
    if (data().is_wait())
        term::pause();
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
    text.draw(data().text());
    Point textBlockUsedSize = text.getUsedSize() + margin;

    auto &brd = data().border();

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

    if (data().icon().has_value()) {
        cvs.getCursorPos().getX()++;
        cvs.draw(StyledChar('[', brd.getColor()));
        cvs.draw(data().icon().value());
        cvs.draw(StyledChar(']', brd.getColor()));
    }

    if (data().caption().has_value()
        && (cvs.getCursorPos().getX() + 3 < cvs.getSize().getX() - 2)) {
        cvs.getCursorPos().getX()++;
        cvs.draw(StyledChar('[', brd.getColor()));
        auto captionWidth = cvs.getSize().getX() - cvs.getCursorPos().getX() - 3;
        auto caption = cvs.extract(cvs.getCursorPos(),
                                   Point(captionWidth, 1));
        caption.draw(data().caption().value());
        cvs.getCursorPos().getX() += captionWidth;
        cvs.draw(StyledChar(']', brd.getColor()));
    }
}

}



