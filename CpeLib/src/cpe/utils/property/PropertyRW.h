#pragma once

#include <utility>

#include "IProperty.h"
#include "AProperty.h"
#include "IPropertyWrite.h"
#include "IPropertyRead.h"

namespace cpe {

template<class TValue>
class PropertyRW : public AProperty<TValue>,
                   public IPropertyWrite<TValue>,
                   public IPropertyRead<TValue> {
    friend class AProperties;

public:
    PropertyRW();

    explicit PropertyRW(const TValue &defValue);

    TValue &operator()() const override;

    void operator()(const TValue &value) override;

    void operator()(IPropertyRead &prop) override;

    template<class TProperty>
    void bind(TProperty &prop);
};

template<class TValue>
PropertyRW<TValue>::PropertyRW() : AProperty<TValue>() {

}

template<class TValue>
PropertyRW<TValue>::PropertyRW(const TValue &defValue) {
    AProperty<TValue>::mValue = new TValue(defValue);
}

template<class TValue>
TValue &PropertyRW<TValue>::operator()() const {
    return *(AProperty<TValue>::_get(true));
}

template<class TValue>
void PropertyRW<TValue>::operator()(const TValue &value) {
    AProperty<TValue>::_set(true, value, true);
}

template<class TValue>
void PropertyRW<TValue>::operator()(IPropertyRead &prop) {
    auto aProp = dynamic_cast<AProperty *>(&prop);
    if (aProp != this && aProp->mBindProp != this) {
        this->_set(true, aProp->_get(true), true);
    }
}

template<class TValue>
template<class TProperty>
void PropertyRW<TValue>::bind(TProperty &prop) {
    if (!std::is_base_of<IProperty, TProperty>::value)
            static_assert("'TProperty' не дочерний тип 'IProperty'");
    if (std::is_base_of<IPropertyRead, TProperty>::value) {
        // TODO закончить с биндингом
    }
}

}


