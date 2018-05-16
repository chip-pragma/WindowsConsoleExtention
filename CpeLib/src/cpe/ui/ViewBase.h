#pragma once

#include "cpe/ui/write/WriteHelper.h"

namespace cpe {

template<class TController>
class ViewBase : WriteHelper {
public:
    using ControllerType = TController;

    virtual TController &create_controller();

    virtual void show(bool beforeClean, bool afterClean) final;

protected:
    virtual void work() = 0;

private:
};

template<class TController>
void ViewBase<TController>::show(bool beforeClean, bool afterClean) {
    if (beforeClean)
        term::clear();

    if (afterClean)
        state_save();

    work();

    if (afterClean)
        state_clear_back();
}

}