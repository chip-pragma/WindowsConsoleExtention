#pragma once

#include "ObserverInterface.h"
#include "ProviderInterface.h"

namespace cpe {

class ControllerInterface : public ObserverInterface,
                           public ProviderInterface {
public:
    ~ControllerInterface() override {};
};

}




