#include "cpe/tool/Encoder.h"
#include "IWriter.h"
#include "Notification.h"

namespace cpe {

//region [ Initializer ]

Notification::Initializer::Initializer(Notification &element) :
        IInitializer(static_cast<IWriter &>(element)),
        mElement(element) { }

Notification::~Notification() { }

StyledBorder &Notification::Initializer::border() {
    return mElement.border();
}

Nullable<StyledText> &Notification::Initializer::caption() {
    return mElement.caption();
}

StyledText &Notification::Initializer::message() {
    return mElement.message();
}

Nullable<StyledChar> &Notification::Initializer::icon() {
    return mElement.icon();
}

bool Notification::Initializer::is_wait() const {
    return mElement.is_wait();
}

void Notification::Initializer::wait(bool wait) {
    mElement.wait(wait);
}

//endregion

Notification::Notification() {
    mBorder.style().final_encoding().set(Encoder(Encoder::CP866));
}

const StyledBorder &Notification::border() const {
    return mBorder;
}

StyledBorder &Notification::border() {
    return mBorder;
}

const Nullable<StyledText> &Notification::caption() const {
    return mCaption;
}

Nullable<StyledText> &Notification::caption() {
    return mCaption;
}

const StyledText &Notification::message() const {
    return mMessage;
}

StyledText &Notification::message() {
    return mMessage;
}

const Nullable<StyledChar> &Notification::icon() const {
    return mIcon;
}

Nullable<StyledChar> &Notification::icon() {
    return mIcon;
}

bool Notification::is_wait() const {
    return mWait;
}

void Notification::wait(bool wait) {
    mWait = wait;
}

void Notification::draw(Buffer &cvs) {
    using brd = BorderStyle;

    Point innerSize = cvs.size() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.dimension() != Point::DIM_SECTOR_I) {
        cvs.draw(StyledText("[NO PLACE]"));
        return;
    }

    Buffer text = cvs.extract(margin / 2 + Point(1, 1), textBlockSize, false);
    text.draw(mMessage);
    Point textBlockUsedSize = text.calc_used_size() + margin;

    cvs.draw(mBorder[brd::SLT]);
    cvs.draw(mBorder[brd::ST], textBlockUsedSize.x_crd(), false);
    cvs.draw(mBorder[brd::SRT]);

    cvs.cursor_position(Point(0, 1));
    cvs.draw(mBorder[brd::SL], textBlockUsedSize.y_crd(), true);
    cvs.cursor_position(Point(textBlockUsedSize.x_crd() + 1, 1));
    cvs.draw(mBorder[brd::SR], textBlockUsedSize.y_crd(), true);

    cvs.cursor_position(Point(0, textBlockUsedSize.y_crd() + 1));
    cvs.draw(mBorder[brd::SLB]);
    cvs.draw(mBorder[brd::SB], textBlockUsedSize.x_crd(), false);
    cvs.draw(mBorder[brd::SRB]);

    // Open
    cvs.cursor_position(Point(1, 0));

    if (mIcon) {
        cvs.move_cursor(Point(1, 0));
        cvs.draw(StyledText("[", mBorder.color()));
        cvs.draw(mIcon.get());
        cvs.draw(StyledText("]", mBorder.color()));
    }

    if (mCaption
        && (cvs.cursor_position().x_crd() + 3 < cvs.size().x_crd() - 2)) {
        cvs.move_cursor(Point(1, 0));
        cvs.draw(StyledText("[", mBorder.color()));
        auto captionWidth = cvs.size().x_crd() - cvs.cursor_position().x_crd() - 3;
        auto caption = cvs.extract(cvs.cursor_position(),
                                   Point(captionWidth, 1));
        caption.draw(mCaption.get());
        cvs.move_cursor(Point(captionWidth, 0));
        cvs.draw(StyledText("]", mBorder.color()));
    }
}

void Notification::output_to(std::ostream &outStream, const Point &size) {
    WriterBase::output_to(outStream, size);
    if (mWait)
        term::pause();
}

}



