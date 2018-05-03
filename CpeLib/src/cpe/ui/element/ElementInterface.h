#pragma once

#include "cpe/ui/ViewInterface.h"
#include "cpe/ui/ControllerInterface.h"
#include "cpe/ui/BufferOld.h"

namespace cpe {

class ElementInterface {
public:
    virtual void run(ControllerInterface &controller, BufferOld &out) = 0;

};

}


