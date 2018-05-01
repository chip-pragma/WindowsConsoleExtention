#pragma once

#include <cpe/ui/property/PropertyObserverInterface.h>

namespace cpe {

class ViewInterface : public PropertyObserverInterface {
public:
    virtual void run() = 0;
};

}