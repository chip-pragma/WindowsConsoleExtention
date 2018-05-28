#pragma once

#include "BaseMenuItem.h"

namespace cpe {

class MenuSeparator : public BaseMenuItem {
public:


    void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const override;
};

}




