#pragma once

#include "PropertyManagerAbstract.h"
#include "ObserverInterface.h"
#include "ProviderInterface.h"

namespace cpe {

template<class TValue>
class Property {
    friend class PropertyManagerAbstract;

public:
    using ValueType = TValue;

    template<class TObserver>
    using ObserverSetFunc = bool (TObserver::*)(const ValueType &);

    template<class TProvider>
    using ProviderGetFunc = const ValueType &(TProvider::*)();

    Property() = default;

    explicit Property(const ValueType& value);

    Property(const Property<ValueType>& prop);

    Property(Property<ValueType>&& prop) noexcept;

    ValueType &get();

    void set(const ValueType &value);

    template<class TObserver>
    void assignObserver(ObserverSetFunc<TObserver> func);

    void rejectObserver();

    template<class TProvider>
    void assignProvider(ProviderGetFunc<TProvider> func);

    void rejectProvider();

private:
    using PureObserverSetFunc = bool (ObserverInterface::*)(const ValueType &);
    using PureProviderGetFunc = const ValueType &(ProviderInterface::*)();

    ValueType mValue = ValueType();
    PureObserverSetFunc mObserver = nullptr;
    PureProviderGetFunc mProvider = nullptr;
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
    mObserver = prop.mObserver;
    mProvider = prop.mProvider;
    prop.mObserver = nullptr;
    prop.mProvider = nullptr;
}

template<class TValue>
ValueType &Property<TValue>::get() {
    return mValue;
}

template<class TValue>
void Property<TValue>::set(const ValueType &value) {
    mValue = value;
}

template<class TValue>
template<class TObserver>
void Property<TValue>::assignObserver(Property::ObserverSetFunc<TObserver> func) {
    mObserver = static_cast<PureObserverSetFunc>(func);
}

template<class TValue>
void Property<TValue>::rejectObserver() {
    mObserver = nullptr;
}

template<class TValue>
template<class TProvider>
void Property<TValue>::assignProvider(Property::ProviderGetFunc<TProvider> func) {
    mProvider = static_cast<PureProviderGetFunc>(func);
}

template<class TValue>
void Property<TValue>::rejectProvider() {
    mProvider = nullptr;
}

}
