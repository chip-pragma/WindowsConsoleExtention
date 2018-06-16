#pragma once

#include "IMenuItem.h"

namespace wce {

class BaseMenuItem : public IMenuItem {
public:
    StyledText text;

    ~BaseMenuItem() override;
};

}


