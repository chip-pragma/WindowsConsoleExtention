#include "Item.h"

namespace cw {

std::string Item::getName() const {
    return _name;
}

std::string Item::getDescription() const {
    return _description;
}

std::string Item::getBuildNumber() const {
    return _buildNumber;
}

std::string Item::getItemNumber() const {
    return _itemNumber;
}

}