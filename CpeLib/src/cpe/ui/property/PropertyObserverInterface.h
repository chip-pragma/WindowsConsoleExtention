#pragma once

#include "PropertyInterface.h"

namespace cpe {

class PropertyObserverInterface {

public:
    virtual void handlePropertyChanged(PropertyInterface& changedProperty) = 0;

};

}




