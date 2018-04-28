#pragma once

#include "cpe/macros.h"
#include "IProperty.h"

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

class AProperties;

template<class TValue>
class AProperty : public IProperty {
    friend class AProperties;

public:
    AProperty();

    ~AProperty() override;

    AProperty<TValue> &operator=(const AProperty<TValue> &prop) = delete;

    AProperty<TValue> &operator=(AProperty<TValue> &&value) = delete;

    /**
     * Отменяет синхронизацию
     */
    void unbind();

protected:
    AProperty<TValue> *mBindProp = nullptr;
    AProperties *mOwner = nullptr;
    TValue *mValue;

    CustomGetterFunc<AProperties, TValue> mGetter = nullptr;
    CustomSetterFunc<AProperties, TValue> mSetter = nullptr;

    /**
     * Задает новое значение через семантику перемещения
     * @param viaSetter использовать пользовательский сеттер (если назначен)?
     * @param value новое значение
     */
    virtual void _set(bool viaSetter, TValue *value, bool binding);

    /**
     * Возвращает значение свойства
     * @param viaGetter использовать пользовательский геттер (если назначен)?
     */
    TValue *_get(bool viaGetter) const;

};

template<class TValue>
AProperty<TValue>::AProperty() {
    mValue = new TValue();
}

template<class TValue>
AProperty<TValue>::~AProperty() {
    unbind();
    delete mValue;
}

template<class TValue>
void AProperty<TValue>::unbind() {
    if (mBindProp != nullptr) {
        mBindProp->mBindProp = nullptr;
        mBindProp = nullptr;
    }
}

template<class TValue>
void AProperty<TValue>::_set(bool viaSetter, TValue *value, bool binding) {
    if (*mValue != value) {
        if (viaSetter && mSetter != nullptr)
            (mOwner->*mSetter)(value);
        else
            *mValue = value;
    }

    if (binding && mBindProp != nullptr)
        mBindProp->_set(true, _get(true), false);
}

template<class TValue>
TValue *AProperty<TValue>::_get(bool viaGetter) const {
    if (viaGetter && mGetter != nullptr)
        return &(mOwner->*mGetter)();
    return mValue;
}

}


