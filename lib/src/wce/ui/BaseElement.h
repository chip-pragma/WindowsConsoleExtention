#pragma once

#include <vector>
#include <algorithm>

#include "IElement.h"
#include "wce/core/Event.h"

namespace wce {

template<class TDerived>
class BaseElement : public IElement {
    using Type = BaseElement<TDerived>;
public:
//    template<class TScript>
//    using BeforeRunCallback = void (TScript::*)(TDerived &);

    Event<Type, TDerived&> eventBeforeRun;
    Event<Type, TDerived&> eventAfterRun;

    BaseElement() = default;

//    BaseElement(const BaseElement<TDerived>& elem);

    ~BaseElement() override { };

//     TODO разработать систему событий

//    template<class TScript>
//    void addBeforeRunCallback(BeforeRunCallback<TScript> func);
//
//    template<class TScript>
//    void removeBeforeRunCallback(BeforeRunCallback<TScript> func);

protected:
//    void callBeforeRun(BaseScript &script);

    void onBeforeRun() override;

    void onAfterRun() override;

private:
//    using _PureBeforeRunCallback = void (BaseScript::*)(TDerived &);

//    std::vector<_PureBeforeRunCallback> m_beforeRunCallbackVec;
};

//region declaration

template<class TDerived>
void BaseElement<TDerived>::onBeforeRun() {
    eventBeforeRun.fire(static_cast<TDerived &>(*this));
}

template<class TDerived>
void BaseElement<TDerived>::onAfterRun() {
    eventAfterRun.fire(static_cast<TDerived &>(*this));
}

//template<class TDerived>
//BaseElement<TDerived>::BaseElement(const BaseElement<TDerived> &elem) {
//    // FIXME не копируется указатель на функцию-член
//    auto elemVecData = elem.m_beforeRunCallbackVec.data();
//    for (size_t i = 0; i < elem.m_beforeRunCallbackVec.size(); ++i) {
//        this->m_beforeRunCallbackVec.push_back(elemVecData[i]);
//    }
//}

//template<class TDerived>
//template<class TScript>
//void BaseElement<TDerived>::addBeforeRunCallback(BeforeRunCallback<TScript> func) {
//    auto castedFunc = static_cast<_PureBeforeRunCallback>(func);
//    bool anyOf = std::any_of(
//        m_beforeRunCallbackVec.begin(),
//        m_beforeRunCallbackVec.end(),
//        [=](const _PureBeforeRunCallback& f) {
//            return f == castedFunc;
//        });
//    if (anyOf)
//        return;
//    m_beforeRunCallbackVec.push_back(castedFunc);
//}

//template<class TDerived>
//template<class TScript>
//void BaseElement<TDerived>::removeBeforeRunCallback(BaseElement::BeforeRunCallback<TScript> func) {
//    auto castedFunc = static_cast<_PureBeforeRunCallback>(func);
//    auto find = std::find(m_beforeRunCallbackVec.begin(), m_beforeRunCallbackVec.end(), castedFunc);
//    if (find != m_beforeRunCallbackVec.end())
//        m_beforeRunCallbackVec.erase(find);
//}

//template<class TDerived>
//void BaseElement<TDerived>::callBeforeRun(BaseScript &script) {
//    for (auto callback : m_beforeRunCallbackVec)
//        (script.*callback)(*static_cast<TDerived*>(this));
//}

//endregion

}





