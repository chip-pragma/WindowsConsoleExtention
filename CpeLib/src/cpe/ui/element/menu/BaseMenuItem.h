#pragma once

#include "IMenuItem.h"

namespace cpe {

class BaseMenuItem : public IMenuItem {
public:
    const bool &visible() const override;

    bool &visible() override;

protected:
    bool mVisible;
};

}


