#pragma once

#include "cpe/ui/ViewInterface.h"
#include "cpe/ui/ControllerInterface.h"
#include "cpe/ui/TextCanvas.h"

namespace cpe {

class ElementInterface {
public:
    virtual void run(ControllerInterface &controller, TextCanvas &out) = 0;

};

}


