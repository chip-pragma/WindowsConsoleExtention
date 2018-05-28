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

void Notification::on_write(Buffer &cvs) {
    using BS = BorderStyle;

    Point innerSize = cvs.get_size() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.dimension() != Point::DIM_SECTOR_I) {
        cvs.draw(StyledText().append("[NO PLACE]"));
        return;
    }

    Buffer text = cvs.extract(margin / 2 + Point(1, 1), textBlockSize, false);
    text.draw(data().text());
    Point textBlockUsedSize = text.get_used_size() + margin;

    auto &brd = data().border();

    cvs.draw(brd[BS::SLT]);
    cvs.draw(brd[BS::ST], textBlockUsedSize.x_crd(), false);
    cvs.draw(brd[BS::SRT]);

    cvs.cursor_position() = Point(0, 1);
    cvs.draw(brd[BS::SL], textBlockUsedSize.y_crd(), true);
    cvs.cursor_position() = Point(textBlockUsedSize.x_crd() + 1, 1);
    cvs.draw(brd[BS::SR], textBlockUsedSize.y_crd(), true);

    cvs.cursor_position() = Point(0, textBlockUsedSize.y_crd() + 1);
    cvs.draw(brd[BS::SLB]);
    cvs.draw(brd[BS::SB], textBlockUsedSize.x_crd(), false);
    cvs.draw(brd[BS::SRB]);

    // Open
    cvs.cursor_position() = Point(1, 0);

    if (data().icon().has_value()) {
        cvs.cursor_position().x_crd()++;
        cvs.draw(StyledChar('[', brd.color()));
        cvs.draw(data().icon().value());
        cvs.draw(StyledChar(']', brd.color()));
    }

    if (data().caption().has_value()
        && (cvs.cursor_position().x_crd() + 3 < cvs.get_size().x_crd() - 2)) {
        cvs.cursor_position().x_crd()++;
        cvs.draw(StyledChar('[', brd.color()));
        auto captionWidth = cvs.get_size().x_crd() - cvs.cursor_position().x_crd() - 3;
        auto caption = cvs.extract(cvs.cursor_position(),
                                   Point(captionWidth, 1));
        caption.draw(data().caption().value());
        cvs.cursor_position().x_crd() += captionWidth;
        cvs.draw(StyledChar(']', brd.color()));
    }
}

}



