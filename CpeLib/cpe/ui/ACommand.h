#pragma once

#include "AProcessor.h"
#include "Buffer.h"

namespace cpe {

class ACommand {
public:
    virtual void run() = 0;
};

}


