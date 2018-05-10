#pragma once

#include "cpe/ui/write/WriteHelper.h"

namespace cpe {

class IView {
public:
    virtual void show() = 0;
};

}