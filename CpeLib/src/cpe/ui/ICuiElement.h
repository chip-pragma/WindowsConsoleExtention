#pragma once

#include "IViewModel.h"

namespace cpe {

class ICuiElement {
public:
    virtual~ICuiElement() { };

    virtual void run(IViewModel &ctrl) = 0;
};

}




