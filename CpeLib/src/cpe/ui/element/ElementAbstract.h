#pragma once

#include "cpe/ui/ViewInterface.h"
#include "cpe/ui/ControllerInterface.h"
#include "cpe/ui/Buffer.h"

namespace cpe {

class ElementAbstract {
public:
    virtual void run(ControllerInterface &controller) = 0;

    Buffer& buffer() {
        return mBuffer;
    }

protected:
    Buffer mBuffer;

};

}


