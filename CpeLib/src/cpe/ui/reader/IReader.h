#pragma once

#include "cpe/ui/ICuiElement.h"

namespace cpe {

class IReader : public ICuiElement {
public:
    ~IReader() override { };

    virtual void read() = 0;
};

}

