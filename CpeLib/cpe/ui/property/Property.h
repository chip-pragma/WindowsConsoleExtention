#pragma once

#include "cpe/ui/property/IProperty.h"

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
 * Свойство для чтения и записи
 * @tparam TValue Тип значения свойства
 */
template<class TValue>
class Property : public IProperty {
    friend class cpe::AProperties;

public:
    ~Property();

    /**
     * Задает значение свойства
     */
    void set(const TValue &value);

    /**
     * Возвращает значение свойства
     */
    const TValue &get() const;

    /**
     * Задает свойство для синхронизации значений (биндинг)
     * @param prop синхронизироемое свойство
     */
    void sync(Property<TValue> *prop);

    /**
     * Отменяет синхронизацию
     */
    void unsync();

    /**
     * Возвращает синхронное свойство
     */
    Property<TValue> *syncProperty() const;

protected:
    explicit Property(AProperties *owner) : IProperty(owner) {}

    /**
     * Задает новое значение
     * @param value новое значение
     * @param sync true, если синхронизировать со связанным свойством
     */
    void _set(const TValue &value, bool sync);

    const TValue &_get() const;

    TValue mValue = TValue();
    Property<TValue> *mSyncProp = nullptr;

    CustomGetterFunc<AProperties, TValue> mGetter = nullptr;
    CustomSetterFunc<AProperties, TValue> mSetter = nullptr;
};

template<class TValue>
Property<TValue>::~Property() {
    unsync();
}

template<class TValue>
const TValue &Property<TValue>::get() const {
    return _get();
}

template<class TValue>
void Property<TValue>::set(const TValue &value) {
    _set(value, true);
}

template<class TValue>
void Property<TValue>::sync(Property<TValue> *prop) {
    if (mSyncProp == nullptr) {
        this->mSyncProp = prop;
        prop->mSyncProp = this;
        prop->_set(this->_get(), false);
    }
}

template<class TValue>
void Property<TValue>::unsync() {
    if (mSyncProp != nullptr) {
        mSyncProp->mSyncProp = nullptr;
        mSyncProp = nullptr;
    }
}

template<class TValue>
Property<TValue> *Property<TValue>::syncProperty() const {
    return mSyncProp;
}

template<class TValue>
void Property<TValue>::_set(const TValue &value, bool sync) {
    if (mValue != value) {
        if (mSetter != nullptr)
            (mOwner->*mSetter)(value);
        else
            mValue = value;
    }

    if (sync && mSyncProp != nullptr)
        mSyncProp->_set(_get(), false);
}

template<class TValue>
const TValue &Property<TValue>::_get() const {
    if (mGetter != nullptr)
        return (mOwner->*mGetter)();
    return mValue;
}
}

