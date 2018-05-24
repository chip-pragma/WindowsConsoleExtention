#pragma once

#include <cstdint>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/output/StyledBorder.h"

namespace cpe {

class IMenuItem {
public:
    virtual void write(Buffer &buf, const StyledBorder &sBord) const = 0;
};

}




