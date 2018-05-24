#include "TextMenuItem.h"

namespace cpe {

TextMenuItem::TextMenuItem(uint32_t itemId)
        : mItemId(itemId) { }

TextMenuItem::TextMenuItem(uint32_t itemId, const std::string &text)
        : mItemId(itemId),
          mText(text) { }

uint32_t TextMenuItem::item_id() const {
    return mItemId;
}

const std::string &TextMenuItem::text() const {
    return mText;
}

std::string &TextMenuItem::text() {
    return mText;
}

void TextMenuItem::write(cpe::Buffer &buf, const cpe::StyledBorder &sBord) const {
    //TODO Рисование пункта меню
}

}


