#include "BaseElementData.h"


cpe::BaseElementData::~BaseElementData() { }

const bool &cpe::BaseElementData::getVisible() const {
    return mVisible;
}

bool &cpe::BaseElementData::getVisible() {
    return mVisible;
}
