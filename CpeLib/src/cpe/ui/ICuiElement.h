#pragma once

#include "IController.h"

namespace cpe {

class ICuiElement {
public:
    virtual~ICuiElement() { };

    virtual void run(IController &ctrl) = 0;
};

}




