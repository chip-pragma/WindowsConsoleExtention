#pragma once

#include <cstdint>

#include "wce/ui/output/Buffer.h"
#include "wce/ui/output/StyledBorder.h"

namespace wce {

class IMenuItem {
public:
    virtual const bool& getVisible() const = 0;

    virtual void setVisible(bool vis) = 0;

    virtual void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const = 0;
};

}




