#pragma once

#include "cpe/ui/write/WriteHelper.h"

namespace cpe {

class ViewBase : WriteHelper {
public:
    virtual void show(bool beforeClean, bool afterClean) final;

protected:
    virtual void work() = 0;
};

}