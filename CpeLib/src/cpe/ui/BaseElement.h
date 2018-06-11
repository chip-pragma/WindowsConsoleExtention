#pragma once

#include "IElement.h"

namespace cpe {

template<class TDerived>
class BaseElement : public IElement {
public:
    template<class TScript>
    using BeforeRunListenerFunc = void (TScript::*)(TDerived &);

    ~BaseElement() override { };

    const bool &getVisible() const override;

    void setVisible(bool value) override;

    const bool &isCallPause() const override;

    void setCallPause(bool value) override;

    template<class TScript>
    void addBeforeRunListener(BeforeRunListenerFunc<TScript> func);

protected:
    using _PureBeforeRunListenerFunc = void (BaseScript::*)(TDerived &);

    void fireData(BaseScript &script);

private:
    bool mVisible = true;
    bool mCallPause = false;
    _PureBeforeRunListenerFunc mBeforeRunListenerFunc = nullptr;
};

template<class TDerived>
const bool &BaseElement<TDerived>::getVisible() const {
    return mVisible;
}

template<class TDerived>
void BaseElement<TDerived>::setVisible(bool value) {
    mVisible = value;
}

template<class TDerived>
const bool &BaseElement<TDerived>::isCallPause() const {
    return mCallPause;
}

template<class TDerived>
void BaseElement<TDerived>::setCallPause(bool value) {
    mCallPause = value;
}

template<class TDerived>
template<class TScript>
void BaseElement<TDerived>::addBeforeRunListener(BeforeRunListenerFunc<TScript> func) {
    mBeforeRunListenerFunc = static_cast<_PureBeforeRunListenerFunc>(func);
}

template<class TDerived>
void BaseElement<TDerived>::fireData(BaseScript &script) {
    if (mBeforeRunListenerFunc)
        (script.*mBeforeRunListenerFunc)(*this);
}

}




