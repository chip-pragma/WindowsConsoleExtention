#include "BaseElementData.h"


cpe::BaseElementData::~BaseElementData() { }

const bool &cpe::BaseElementData::visible() const {
    return mVisible;
}

bool &cpe::BaseElementData::visible() {
    return mVisible;
}
