#pragma once

#include "cpe/core/WriterFormat.h"

namespace cpe::ui {

class IWriter {
public:

    virtual void write() = 0;
};

}




