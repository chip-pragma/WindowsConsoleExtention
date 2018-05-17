#pragma once

#include "cpe/ui/IController.h"
#include "cpe/ui/ICuiElement.h"

namespace cpe {

class IViewItem {
public:
    explicit IViewItem(ICuiElement &elem) { }

    virtual ~_IViewItem() { }

    virtual void run(IController &ctrl) = 0;
};

}

