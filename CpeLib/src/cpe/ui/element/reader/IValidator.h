#pragma once

#include <vector>
#include <string>

#include "ReaderErrorVector.h"

namespace cpe {

template <class TValue>
class IValidator {
public:
    virtual void operator()(const TValue &value, ReaderErrorVector &outErrors) const = 0;
};

}



