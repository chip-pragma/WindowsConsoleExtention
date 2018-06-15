#pragma once

#include <vector>

#include "IElement.h"

namespace cpe {

template<class TDerived>
class BaseElement : public IElement {
public:
    template<class TScript>
    using BeforeRunCallback = void (TScript::*)(TDerived &);

    ~BaseElement() override { };

    const bool &getVisible() const override;

    void setVisible(bool value) override;

    const bool &isCallPause() const override;

    void setCallPause(bool value) override;

    template<class TScript>
    void addBeforeRunCallback(BeforeRunCallback<TScript> func);

    template<class TScript>
    void removeBeforeRunCallback(BeforeRunCallback<TScript> func);

protected:
    void callBeforeRun(BaseScript &script);

    void onBeforeRun() override { }

    void onAfterRun() override { }

private:
    using _PureBeforeRunCallback = void (BaseScript::*)(TDerived &);

    bool mVisible = true;
    bool mCallPause = false;
    std::vector<_PureBeforeRunCallback> mBeforeRunCallbackVec;
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
void BaseElement<TDerived>::addBeforeRunCallback(BeforeRunCallback<TScript> func) {
    auto castedFunc = static_cast<_PureBeforeRunCallback>(func);
    bool anyOf = std::any_of(
        mBeforeRunCallbackVec.begin(),
        mBeforeRunCallbackVec.end(),
        [=](const _PureBeforeRunCallback& f) {
            return f == castedFunc;
        });
    if (anyOf)
        return;
    mBeforeRunCallbackVec.push_back(castedFunc);
}

template<class TDerived>
template<class TScript>
void BaseElement<TDerived>::removeBeforeRunCallback(BaseElement::BeforeRunCallback<TScript> func) {
    auto castedFunc = static_cast<_PureBeforeRunCallback>(func);
    auto find = std::find(mBeforeRunCallbackVec.begin(), mBeforeRunCallbackVec.end(), castedFunc);
    if (find != mBeforeRunCallbackVec.end())
        mBeforeRunCallbackVec.erase(find);
}

template<class TDerived>
void BaseElement<TDerived>::callBeforeRun(BaseScript &script) {
    for (auto callback : mBeforeRunCallbackVec)
        (script.*callback)(*static_cast<TDerived*>(this));
}

}




