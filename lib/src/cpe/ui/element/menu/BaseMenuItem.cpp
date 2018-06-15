#include "BaseMenuItem.h"

namespace cpe {

const bool &BaseMenuItem::getVisible() const {
    return mVisible;
}

void BaseMenuItem::setVisible(bool vis) {
    mVisible = vis;
}

const StyledText &BaseMenuItem::getText() const {
    return mText;
}

StyledText &BaseMenuItem::getTextRef() {
    return mText;
}

}


