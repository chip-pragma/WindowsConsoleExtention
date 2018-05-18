#pragma once

#include "cpe/ui/ICuiElement.h"
#include "cpe/ui/output/Buffer.h"

namespace cpe {

class IWriter : public ICuiElement {
public:
    ~IWriter() override { };

    virtual void draw(Buffer &cvs) = 0;
};

}



