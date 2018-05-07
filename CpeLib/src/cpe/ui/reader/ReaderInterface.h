#pragma once

#include "cpe/ui/ConsoleApplication.h"
#include "cpe/tool/property/ObserverInterface.h"

namespace cpe {

class ReaderInterface {
public:
    virtual void runRead(ConsoleApplication &app, ObserverInterface &observer) = 0;
};

}




