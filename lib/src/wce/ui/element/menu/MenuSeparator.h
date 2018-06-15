#pragma once

#include "BaseMenuItem.h"

namespace wce {

class MenuSeparator : public BaseMenuItem {
public:


    void write(Buffer &buf, const StyledBorder &sBord, const TextColor &commandColor) const override;
};

}




