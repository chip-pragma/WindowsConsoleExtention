#pragma once

#include "ObserverInterface.h"
#include "ProviderInterface.h"

namespace cpe {

class PropertyManagerAbstract;

template<class TValue>
class Property {
    friend class PropertyManagerAbstract;

public:
    using ValueType = TValue;

    template<class TObserver>
    using ObserverSetFunc = void (TObserver::*)(const ValueType &);

    template<class TProvider>
    using ProviderGetFunc = const ValueType &(TProvider::*)();

    Property() = default;

    explicit Property(const ValueType &value);

    template<class TObserver>
    void assignObserver(ObserverSetFunc<TObserver> func);

    void rejectObserver();

    template<class TProvider>
    void assignProvider(ProviderGetFunc<TProvider> func);

    void rejectProvider();

    ValueType &operator()();

    void operator()(const ValueType &value);

private:
    using PureObserverSetFunc = bool (ObserverInterface::*)(const ValueType &);
    using PureProviderGetFunc = const ValueType &(ProviderInterface::*)();

    ValueType mValue = ValueType();
    PureObserverSetFunc mObserverFunc = nullptr;
    PureProviderGetFunc mProviderFunc = nullptr;

    Property(const Property<ValueType> &prop);

    Property(Property<ValueType> &&prop) noexcept;

    void _getFromProvider(ProviderInterface &provider);

    void _setToObserver(ObserverInterface &observer);
};

template<class TValue>
Property<TValue>::Property(const ValueType &value) {
    mValue = value;
}

template<class TValue>
Property<TValue>::Property(const Property<ValueType> &prop) {
    mValue = prop.mValue;
}

template<class TValue>
Property<TValue>::Property(Property<ValueType> &&prop) noexcept {
    mValue = prop.mValue;
    mObserverFunc = prop.mObserverFunc;
    mProviderFunc = prop.mProviderFunc;
    prop.mObserverFunc = nullptr;
    prop.mProviderFunc = nullptr;
}

template<class TValue>
template<class TObserver>
void Property<TValue>::assignObserver(Property::ObserverSetFunc<TObserver> func) {
    mObserverFunc = static_cast<PureObserverSetFunc>(func);
}

template<class TValue>
void Property<TValue>::rejectObserver() {
    mObserverFunc = nullptr;
}

template<class TValue>
template<class TProvider>
void Property<TValue>::assignProvider(Property::ProviderGetFunc<TProvider> func) {
    mProviderFunc = static_cast<PureProviderGetFunc>(func);
}

template<class TValue>
void Property<TValue>::rejectProvider() {
    mProviderFunc = nullptr;
}

template<class TValue>
void Property<TValue>::_getFromProvider(ProviderInterface &provider) {
    if (mProviderFunc)
        mValue = (provider.*mProviderFunc)();
}

template<class TValue>
void Property<TValue>::_setToObserver(ObserverInterface &observer) {
    if (mObserverFunc)
        (observer.*mObserverFunc)(mValue);
}

template<class TValue>
typename Property<TValue>::ValueType &Property<TValue>::operator()() {
    return mValue;
}

template<class TValue>
void Property<TValue>::operator()(const ValueType &value) {
    mValue = value;
}

}
