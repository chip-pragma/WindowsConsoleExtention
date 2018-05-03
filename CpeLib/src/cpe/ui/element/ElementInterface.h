#pragma once

#include "cpe/ui/ViewInterface.h"
#include "cpe/ui/ControllerInterface.h"
#include "cpe/ui/Buffer.h"

namespace cpe {

class ElementInterface {
public:
    virtual void run(ControllerInterface &controller, Buffer &out) = 0;

};

}


