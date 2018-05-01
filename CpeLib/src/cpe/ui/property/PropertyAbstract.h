#pragma once

#include "cpe/macros.h"
#include "PropertyException.h"
#include "PropertyInterface.h"
#include "PropertyReadInterface.h"
#include "PropertyWriteInterface.h"

namespace cpe {

/**
 * Указатель на функцию, которая выполняется после возврата значения геттером Property<TValue>
 * @tparam TIPropCommand Дочерний класс ACommand с реализацией IProperties
 * @tparam TValue Тип значения свойства
 */
template<class TIPropCommand, class TValue>
using CustomGetterFunc = TValue &(TIPropCommand::*)();

/**
 * Указатель на функцию, которая выполняется до принятия значения сеттером Property<TValue>
 * @tparam TIPropCommand Дочерний класс ACommand с реализацией IProperties
 * @tparam TValue Тип значения свойства
 */
template<class TIPropCommand, class TValue>
using CustomSetterFunc = void (TIPropCommand::*)(const TValue &);

class PropertyProviderAbstract;

template<class TValue>
class PropertyAbstract : public PropertyInterface {
    friend class PropertyProviderAbstract;

public:
    PropertyAbstract();

    ~PropertyAbstract() override;

    PropertyAbstract<TValue> &operator=(const PropertyAbstract<TValue> &prop) = delete;

    PropertyAbstract<TValue> &operator=(PropertyAbstract<TValue> &&value) = delete;

protected:
    PropertyProviderAbstract *mOwner = nullptr;
    TValue *mValue;

    CustomGetterFunc<PropertyProviderAbstract, TValue> mGetter = nullptr;
    CustomSetterFunc<PropertyProviderAbstract, TValue> mSetter = nullptr;

    virtual void set(bool viaSetter, const TValue *value);

    TValue *get(bool viaGetter) const;
};

template<class TValue>
PropertyAbstract<TValue>::PropertyAbstract() {
    mValue = new TValue();
}

template<class TValue>
PropertyAbstract<TValue>::~PropertyAbstract() {
    delete mValue;
}

template<class TValue>
void PropertyAbstract<TValue>::set(bool viaSetter, const TValue *value) {
    if (mValue != value) {
        if (viaSetter && mSetter != nullptr)
            (mOwner->*mSetter)(*value);
        else
            *mValue = *value;
    }
}

template<class TValue>
TValue *PropertyAbstract<TValue>::get(bool viaGetter) const {
    if (viaGetter && mGetter != nullptr)
        return &(mOwner->*mGetter)();
    return mValue;
}

}


