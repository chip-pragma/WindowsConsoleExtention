#pragma once

#include "IViewModel.h"

namespace cpe {

class ICuiElement {
public:
    virtual~ICuiElement() { };

    virtual void run(IViewModel &ctrl) = 0;

protected:
    virtual void on_before_run() = 0;

    virtual void on_after_run() = 0;
};

}




