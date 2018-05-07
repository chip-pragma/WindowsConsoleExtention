#pragma once

#include "cpe/ui/ViewInterface.h"
#include "cpe/ui/ControllerAbstract.h"
#include "cpe/ui/print/TextCanvas.h"
#include "cpe/ui/reader/ReaderManager.h"

namespace cpe {

class ElementInterface {
public:
    virtual void run(ControllerAbstract &controller, TextCanvas &out, ReaderManager &readers) = 0;

};

}


