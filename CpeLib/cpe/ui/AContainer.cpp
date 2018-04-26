#include "AContainer.h"

namespace cpe {

AContainer::~AContainer() {
    for (auto item : mItemList)
        delete item;
    mItemList.clear();
}

const std::vector<ACommand *> &AContainer::items() const {
    return mItemList;
}

}