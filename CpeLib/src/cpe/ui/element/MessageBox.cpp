#include "cpe/tool/Encoder.h"
#include "MessageBox.h"

namespace cpe {

MessageBox::MessageBox() {
    mBorder.border().final_encoding().set(Encoder(Encoder::CP866));
}

const StyledBorder &MessageBox::border() const {
    return mBorder;
}

StyledBorder &MessageBox::border() {
    return mBorder;
}

const Nullable<StyledText> &MessageBox::caption() const {
    return mCaption;
}

Nullable<StyledText> &MessageBox::caption() {
    return mCaption;
}

const StyledText &MessageBox::message() const {
    return mMessage;
}

StyledText &MessageBox::message() {
    return mMessage;
}

const Nullable<StyledChar> &MessageBox::icon() const {
    return mIcon;
}

Nullable<StyledChar> &MessageBox::icon() {
    return mIcon;
}

void MessageBox::draw(Buffer &cvs) {
    using brd = Border;

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
    cvs.cursor_position(Point(cvs.size().x_crd() - 1, 1));
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

}



