#pragma once

#include "cpe/core/Exception.h"

namespace cpe {

class PropertyException : public Exception {
public:
    PropertyException(const std::string &message);
};

}

