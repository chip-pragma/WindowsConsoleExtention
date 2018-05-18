#pragma once

#include "cpe/ui/IController.h"
#include "cpe/ui/ICuiElement.h"

namespace cpe {

class IViewItem {
public:
    virtual ~IViewItem() { }

    virtual void run(IController &ctrl) = 0;
};

}

