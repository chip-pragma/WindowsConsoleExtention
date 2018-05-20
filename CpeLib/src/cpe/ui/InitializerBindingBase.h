#pragma once

#include "IController.h"

namespace cpe {

template<class TInitializer>
class InitializerBindingBase {
public:
    virtual ~InitializerBindingBase() { };

    template<class TController>
    using InitializerReceiverFunc = void (TController::*)(TInitializer &);

    template<class TController>
    void bind_initializer_func(InitializerReceiverFunc<TController> func);

    void fire_initializer(IController &ctrl, TInitializer &initializer);

protected:
    using _PureInitializerReceiverFunc = void (IController::*)(TInitializer &);

    _PureInitializerReceiverFunc mInitFunc = nullptr;
};

template<class TInitializer>
template<class TController>
void InitializerBindingBase<TInitializer>::bind_initializer_func(InitializerReceiverFunc<TController> func) {
    mInitFunc = static_cast<_PureInitializerReceiverFunc>(func);
}

template<class TInitializer>
void InitializerBindingBase<TInitializer>::fire_initializer(IController &ctrl, TInitializer &initializer) {
    if (mInitFunc)
        (ctrl.*mInitFunc)(initializer);
}

}





