#pragma once

#include "cpe/ui/IWork.h"
#include "ElementBase.h"

namespace cpe {

class ElementWorkBase : public IWork {
public:
    explicit ElementWorkBase(ElementBase &elem) : mElement(elem) { }

protected:
    ElementBase &mElement;
};

}



