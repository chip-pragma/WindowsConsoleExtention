#pragma once

#include <vector>
#include <algorithm>

#include "IElement.h"
#include "wce/core/Event.h"

namespace wce {

template<class TDerived>
class BaseElement : public IElement {
    using _Self = BaseElement<TDerived>;
public:
    Event<_Self, TDerived&> eventBeforeRun;
    Event<_Self, TDerived&> eventAfterRun;

    BaseElement() = default;

    ~BaseElement() override { };

protected:
    void onBeforeRun() override;

    void onAfterRun() override;
};

//region declaration

template<class TDerived>
void BaseElement<TDerived>::onBeforeRun() {
    eventBeforeRun.invoke(static_cast<TDerived &>(*this));
}

template<class TDerived>
void BaseElement<TDerived>::onAfterRun() {
    eventAfterRun.invoke(static_cast<TDerived &>(*this));
}

//endregion

}





