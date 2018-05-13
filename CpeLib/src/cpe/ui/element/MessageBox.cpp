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

const StyledText &MessageBox::caption() const {
    return mCaption;
}

StyledText &MessageBox::caption() {
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

void MessageBox::draw(Buffer &canvas) {
    using brd = Border;

    Point innerSize = canvas.size() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.dimension() != Point::DIM_SECTOR_I) {
        canvas.draw(StyledText("[NO PLACE]"));
        return;
    }

    Buffer text(textBlockSize);
    text.draw(mMessage);
    Point textBlockUsedSize = text.calc_used_size() + margin;

    canvas.draw(mBorder[brd::SLT]);
    canvas.draw(mBorder[brd::ST], textBlockUsedSize.x_crd(), false);
    canvas.draw(mBorder[brd::SRT]);

    canvas.cursor_position(Point(0, 1));
    canvas.draw(mBorder[brd::SL], textBlockUsedSize.y_crd(), true);
    canvas.cursor_position(Point(canvas.size().x_crd() - 1, 1));
    canvas.draw(mBorder[brd::SR], textBlockUsedSize.y_crd(), true);

    canvas.cursor_position(Point(0, textBlockUsedSize.y_crd() + 1));
    canvas.draw(mBorder[brd::SLB]);
    canvas.draw(mBorder[brd::SB], textBlockUsedSize.x_crd(), false);
    canvas.draw(mBorder[brd::SRB]);

    canvas.cursor_position(margin / 2 + Point(1, 1));
    canvas.draw(text, true);
}

}



