#pragma once

#include "PropertyReadInterface.h"

namespace cpe {

template<class TValue>
class PropertyWriteInterface {

public:
    virtual void operator()(const TValue &value) = 0;

};

}