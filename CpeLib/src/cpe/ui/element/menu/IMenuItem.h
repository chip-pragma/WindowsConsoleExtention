#pragma once

#include <cstdint>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/output/StyledBorder.h"

namespace cpe {

class IMenuItem {
public:
    virtual const bool& getVisible() const = 0;

    virtual bool& getVisible() = 0;

    virtual void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const = 0;
};

}




