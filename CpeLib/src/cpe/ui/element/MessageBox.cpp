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

    Point innerSize = canvas.max_size() - Point(2, 2);
    Point margin(2, 0);
    Point textBlockSize = innerSize - margin;
    if (textBlockSize.x < 1 || textBlockSize.y < 1) {
        canvas.draw("[NO PLACE]");
        return;
    }

    TextCanvas text(textBlockSize);
    text.draw(mText);
    Point actualSize = text.actual_size() + margin;

    canvas.draw(mBorder[brd::LT]);
    canvas.draw(std::string(actualSize.x, mBorder[brd::T][0]));
    canvas.draw(mBorder[brd::RT]);
    // TODO предотвратить автоматическтий переход на новую строку (добавить типа политики перехода и т.п.)
    canvas.draw_line();

    for (int i = 0; i < text.actual_size().y; i++) {
        canvas.draw(mBorder[brd::L]);
        canvas.move_cursor(Point(actualSize.x, 0));
        canvas.draw(mBorder[brd::R]);
        canvas.draw_line();
    }

    canvas.draw(mBorder[brd::LB]);
    canvas.draw(std::string(actualSize.x, mBorder[brd::B][0]));
    canvas.draw(mBorder[brd::RB]);

    canvas.cursor_position(margin / 2 + Point(1, 1));
    canvas.draw(text, true);
}

}



