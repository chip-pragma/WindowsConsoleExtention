#pragma once

#include "cpe/core/Exception.h"

namespace cpe {

class ViewException : public Exception {
public:
    ViewException(const std::string &message);

};

}




