#pragma once

#include "IProperty.h"

namespace cpe {

/**
 * Указатель на функцию, которая выполняется после возврата значения геттером Property<TValue>
 * @tparam TIPropCommand Дочерний класс ACommand с реализацией IProperties
 * @tparam TValue Тип значения свойства
 */
template<class TIPropCommand, class TValue>
using CustomGetterFunc = const TValue &(TIPropCommand::*)();
/**
 * Указатель на функцию, которая выполняется до принятия значения сеттером Property<TValue>
 * @tparam TIPropCommand Дочерний класс ACommand с реализацией IProperties
 * @tparam TValue Тип значения свойства
 */
template<class TIPropCommand, class TValue>
using CustomSetterFunc = void (TIPropCommand::*)(const TValue &);

/**
 * Базовый класс для реализации свойств
 * @tparam TValue Тип значения свойства
 */
template<class TValue>
class AProperty : public IProperty {
    friend class cpe::AProperties;

protected:
    explicit AProperty(AProperties *owner);

    // Вызывает геттер по умолчанию или назначенный
    const TValue &_get();

    // Вызывает сеттер по умолчанию или назначенный
    void _set(const TValue &value);

    TValue mValue;

    CustomGetterFunc<AProperties, TValue> mGetter = nullptr;
    CustomSetterFunc<AProperties, TValue> mSetter = nullptr;
};

template<class TValue>
AProperty<TValue>::AProperty(AProperties *owner) : IProperty(owner) {
}

template<class TValue>
const TValue &AProperty<TValue>::_get() {
    if (mGetter != nullptr)
        return (mOwner->*mGetter)();
    return mValue;
}

template<class TValue>
void AProperty<TValue>::_set(const TValue &value) {
    if (mValue != value) {
        if (mSetter != nullptr)
            (mOwner->*mSetter)(value);
        else
            mValue = value;
    }
}

}
