#pragma once

#include "cpe/ui/ViewInterface.h"
#include "cpe/ui/ControllerAbstract.h"
#include "cpe/ui/print/TextCanvas.h"

namespace cpe {

class ElementInterface {
public:
    virtual void run(ControllerAbstract &controller) = 0;

};

}


