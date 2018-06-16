#pragma once

#include <cstdint>

#include "wce/ui/output/Buffer.h"
#include "wce/ui/output/StyledBorder.h"

namespace wce {

class IMenuItem {
public:
    bool visible = true;

    virtual ~IMenuItem() { }

    virtual void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const = 0;
};

}




