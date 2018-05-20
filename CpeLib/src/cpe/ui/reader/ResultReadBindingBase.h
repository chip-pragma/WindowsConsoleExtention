#pragma once

#include "cpe/ui/IController.h"

namespace cpe {

template<class TResult>
class ResultReadBindingBase {
public:
public:
    virtual ~ResultReadBindingBase() { };

    template<class TController>
    using ResultReadReceiverFunc = void (TController::*)(TResult &);

    template<class TController>
    void bind_result_func(ResultReadReceiverFunc<TController> func);

    void fire_result(IController &ctrl, TResult &result);

protected:
    using _PureResultReadReceiverFunc  = void (IController::*)(TResult &);

    _PureResultReadReceiverFunc mResultFunc = nullptr;
};

template<class TResult>
template<class TController>
void ResultReadBindingBase<TResult>::bind_result_func(ResultReadReceiverFunc<TController> func) {
    mResultFunc = static_cast<_PureResultReadReceiverFunc>(func);
}

template<class TResult>
void ResultReadBindingBase<TResult>::fire_result(IController &ctrl, TResult &result) {
    if (mResultFunc)
        (ctrl.*mResultFunc)(result);
}

}


