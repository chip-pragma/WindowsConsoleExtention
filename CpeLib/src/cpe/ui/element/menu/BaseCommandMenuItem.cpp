#include "BaseCommandMenuItem.h"
#include "cpe/tool/text.h"
#include "cpe/core/Exception.h"

namespace cpe {

BaseCommandMenuItem::BaseCommandMenuItem(const std::string &commands) {
    text::split(commands, mCommandList, "|");
    if (mCommandList.empty())
        throw Exception("Menu item command is not set");
}

const bool &BaseCommandMenuItem::getVisible() const {
    return mVisible;
}

bool &BaseCommandMenuItem::getVisible() {
    return mVisible;
}

const MenuItemCommandList & BaseCommandMenuItem::getCommandList() const {
    return mCommandList;
}

}


