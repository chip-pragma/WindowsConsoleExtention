#pragma once

#include "ICuiElement.h"

namespace cpe {

class IInitializer {
public:
    explicit IInitializer(ICuiElement &element) { };

    virtual ~IInitializer() { }
};

}




