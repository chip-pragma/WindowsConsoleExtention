#include "BaseMenuItem.h"

namespace cpe {

const bool &BaseMenuItem::visible() const {
    return mVisible;
}

bool &BaseMenuItem::visible() {
    return mVisible;
}

}


