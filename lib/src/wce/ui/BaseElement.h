#pragma once

#include <vector>
#include <algorithm>

#include "IElement.h"

namespace wce {

template<class TDerived>
class BaseElement : public IElement {
public:
    template<class TScript>
    using BeforeRunCallback = void (TScript::*)(TDerived &);

    ~BaseElement() override { };

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

    std::vector<_PureBeforeRunCallback> m_beforeRunCallbackVec;
};

template<class TDerived>
template<class TScript>
void BaseElement<TDerived>::addBeforeRunCallback(BeforeRunCallback<TScript> func) {
    auto castedFunc = static_cast<_PureBeforeRunCallback>(func);
    bool anyOf = std::any_of(
        m_beforeRunCallbackVec.begin(),
        m_beforeRunCallbackVec.end(),
        [=](const _PureBeforeRunCallback& f) {
            return f == castedFunc;
        });
    if (anyOf)
        return;
    m_beforeRunCallbackVec.push_back(castedFunc);
}

template<class TDerived>
template<class TScript>
void BaseElement<TDerived>::removeBeforeRunCallback(BaseElement::BeforeRunCallback<TScript> func) {
    auto castedFunc = static_cast<_PureBeforeRunCallback>(func);
    auto find = std::find(m_beforeRunCallbackVec.begin(), m_beforeRunCallbackVec.end(), castedFunc);
    if (find != m_beforeRunCallbackVec.end())
        m_beforeRunCallbackVec.erase(find);
}

template<class TDerived>
void BaseElement<TDerived>::callBeforeRun(BaseScript &script) {
    for (auto callback : m_beforeRunCallbackVec)
        (script.*callback)(*static_cast<TDerived*>(this));
}

}




