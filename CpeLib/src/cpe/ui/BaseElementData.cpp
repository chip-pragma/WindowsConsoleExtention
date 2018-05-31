#include "BaseElementData.h"


cpe::BaseElementData::~BaseElementData() { }

const bool &cpe::BaseElementData::getVisible() const {
    return mVisible;
}

void cpe::BaseElementData::setVisible(bool value) {
    mVisible = value;
}

const bool &cpe::BaseElementData::isCallPause() const {
    return mCallPause;
}

void cpe::BaseElementData::setCallPause(bool value) {
    mCallPause = value;
}
