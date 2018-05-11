#pragma once

#include "cpe/core/Exception.h"

namespace cpe {

class NullableException : public Exception {
public:
    explicit NullableException(const std::string &message) : Exception(message) {}
};

}



