#pragma once

#include "cpe/ui/ICuiElement.h"
#include "cpe/ui/output/Buffer.h"

namespace cpe {

class IWriter {
public:
    virtual ~IWriter() { };

    virtual void write(Buffer &buf) = 0;

protected:
    virtual void onWrite(Buffer &buf) = 0;
};

}



