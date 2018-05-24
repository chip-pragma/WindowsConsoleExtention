#pragma once

#include <cstdint>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/output/StyledBorder.h"

namespace cpe {

class IMenuItem {
public:
    virtual const bool& visible() const = 0;

    virtual bool& visible() = 0;

    virtual void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const = 0;

    virtual std::string get_command() const = 0;
};

}




