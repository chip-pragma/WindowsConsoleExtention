#pragma once

#include "property/PropertyProviderAbstract.h"
#include "property/PropertyObservableAbstract.h"

namespace cpe {

class ControllerAbstract : public PropertyProviderAbstract, public PropertyObservableAbstract {
public:
    ~ControllerAbstract() override {};
};

}




