#include "cpe/tool/Encoder.h"
#include "MessageBox.h"

namespace cpe {

MessageBox::MessageBox() {
    mBorder.final_encoding().set(
            Encoder(static_cast<Encoder::Encoding>(
                            term::output_cp())));
}

const DualBorder &MessageBox::border_style() const {
    return mBorder.last_applied();
}

void MessageBox::border_style(const DualBorder &db) {
    mBorder.apply(db);
}

const std::string &MessageBox::caption() const {
    return mCaption;
}

void MessageBox::caption(const std::string &caption) {
    mCaption = caption;
}

const std::string &MessageBox::text() const {
    return mText;
}

void MessageBox::text(const std::string &text) {
    mText = text;
}

const Nullable<StyledChar> &MessageBox::icon() const {
    return mIcon;
}

Nullable<StyledChar> &MessageBox::icon() {
    return mIcon;
}

void MessageBox::icon(const Nullable<StyledChar> &icon) {
    mIcon.set(icon);
}

void MessageBox::draw(TextCanvas &canvas) {
    using brd = Border;

    Point innerSize = canvas.size() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.dimension() != Point::DIM_SECTOR_I) {
        canvas.draw("[NO PLACE]");
        return;
    }

    TextCanvas text(textBlockSize);
    text.draw(mText);
    Point textBlockUsedSize = text.calc_used_size() + margin;

    canvas.draw(mBorder[brd::LT]);
    canvas.draw(mBorder[brd::T][0], textBlockUsedSize.x_crd(), false);
    canvas.draw(mBorder[brd::RT]);

    canvas.cursor_position(Point(0, 1));
    canvas.draw(mBorder[brd::L][0], textBlockUsedSize.y_crd(), true);
    canvas.cursor_position(Point(canvas.size().x_crd() - 1, 1));
    canvas.draw(mBorder[brd::R][0], textBlockUsedSize.y_crd(), true);

    canvas.cursor_position(Point(0, textBlockUsedSize.y_crd() + 1));
    canvas.draw(mBorder[brd::LB]);
    canvas.draw(mBorder[brd::B][0], textBlockUsedSize.x_crd(), false);
    canvas.draw(mBorder[brd::RB]);

    canvas.cursor_position(margin / 2 + Point(1, 1));
    canvas.draw(text, true);
}

}



