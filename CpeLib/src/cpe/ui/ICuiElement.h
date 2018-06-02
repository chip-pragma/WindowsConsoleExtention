#pragma once

#include "IViewModel.h"

namespace cpe {

class ICuiElement {
public:
    virtual~ICuiElement() { };

    virtual void run(IViewModel &ctrl) = 0;

protected:
    virtual void onBeforeRun() = 0;

    virtual void onRun() = 0;

    virtual void onAfterRun() = 0;
};

}




