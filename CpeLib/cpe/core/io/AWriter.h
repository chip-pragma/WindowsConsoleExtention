#pragma once

#include "cpe/core/OutputFormat.h"

namespace cpe::core::io {

class AWriter {
public:
    AWriter();

    virtual void write() = 0;
};

}




