#pragma once

#include <type_traits>
#include "IViewItem.h"
#include "cpe/ui/IInitializer.h"

namespace cpe {

template<class TController, class TInitializer>
class ViewItemBase : public IViewItem {
public:
    using InitializerReceiverFunc = void (TController::*)(TInitializer &);
    using InitializerClass = TInitializer;

    explicit ViewItemBase(ICuiElement &elem, InitializerReceiverFunc initFunc);

    ~ViewItemBase() override { };

protected:
    InitializerReceiverFunc mInitFunc = nullptr;
};

template<class TController, class TInitializer>
ViewItemBase<TController, TInitializer>::ViewItemBase(ICuiElement &elem,
                                                      ViewItemBase::InitializerReceiverFunc initFunc)
        : IViewItem(elem) {
    static_assert(std::is_base_of<IController, TController>::value);
    static_assert(std::is_base_of<IInitializer, TInitializer>::value);
}

}




