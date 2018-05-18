#pragma once

#include <type_traits>
#include "IViewItem.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/IController.h"

namespace cpe {

template<class TElement, class TInitializer>
class ViewItemBase : public IViewItem {
public:
    template<class TController>
    using InitializerReceiverFunc = void (TController::*)(TInitializer &);
    using InitializerClass = TInitializer;

    explicit ViewItemBase(TElement& elem);

    ~ViewItemBase() override { };

    template<class TController>
    void assign_init_func(InitializerReceiverFunc<TController> initFunc);

protected:
    using _PureInitializerReceiverFunc = void (IController::*)(TInitializer &);

    _PureInitializerReceiverFunc mInitFunc = nullptr;
};

template<class TElement, class TInitializer>
ViewItemBase<TElement, TInitializer>::ViewItemBase(TElement& elem) {
    static_assert(std::is_base_of<IInitializer, TInitializer>::value);
}

template<class TElement, class TInitializer>
template<class TController>
void ViewItemBase<TElement, TInitializer>::assign_init_func(InitializerReceiverFunc<TController> initFunc) {
    mInitFunc = static_cast<_PureInitializerReceiverFunc>(initFunc);
}

}




