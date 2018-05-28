#include "BaseMenuItem.h"

namespace cpe {

const bool &BaseMenuItem::getVisible() const {
    return mVisible;
}

bool &BaseMenuItem::getVisible() {
    return mVisible;
}

const StyledText &BaseMenuItem::getText() const {
    return mText;
}

StyledText &BaseMenuItem::getText() {
    return mText;
}

}


