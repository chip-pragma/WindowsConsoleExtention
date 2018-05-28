#include <vector>
#include "BaseSetItemsSource.h"

namespace cpe {

void BaseSetItemsSource::set_items_source(MenuItemMap &items) {
    mItems = &items;
}

}