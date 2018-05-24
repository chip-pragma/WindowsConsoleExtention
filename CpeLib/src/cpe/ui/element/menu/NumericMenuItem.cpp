#include "NumericMenuItem.h"

namespace cpe {

NumericMenuItem::NumericMenuItem(uint32_t index)
        : mIndex(index) { }

NumericMenuItem::NumericMenuItem(uint32_t itemId, const std::string &text)
        : mIndex(itemId),
          mText(text) { }

const uint32_t& NumericMenuItem::index() const {
    return mIndex;
}

uint32_t &NumericMenuItem::index() {
    return mIndex;
}

const StyledText &NumericMenuItem::text() const {
    return mText;
}

StyledText &NumericMenuItem::text() {
    return mText;
}

void NumericMenuItem::write(cpe::Buffer &buf, const cpe::StyledBorder &sBord, const TextColor &commandColor) const {
    using BS = BorderStyle;
    buf.draw(sBord[BS::SL]);
    buf.draw(' ');
    buf.draw(StyledChar('[', sBord.color()));
    buf.draw(StyledString(get_command(), commandColor));
    buf.draw(StyledChar(']', sBord.color()));
    buf.draw(' ');

    auto subBuf = buf.extract(buf.cursor_position(), buf.get_size() - buf.cursor_position());
    subBuf.draw(mText);

    buf.cursor_position().y_crd() += subBuf.get_used_size().y_crd();
}

std::string NumericMenuItem::get_command() const {
    return std::to_string(mIndex);
}

}


