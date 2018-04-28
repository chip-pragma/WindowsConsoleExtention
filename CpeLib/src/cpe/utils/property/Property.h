#pragma once

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

/**
 * Свойство для чтения и записи
 * @tparam TValue Тип значения свойства
 */
template<class TValue>
class Property : public IProperty {
    friend class cpe::AProperties;

public:
    Property<TValue> &operator=(Property<TValue> &prop) = delete;

    Property<TValue> &operator=(Property<TValue> &&value) = delete;

    Property();

    explicit Property(TValue &&defValue);

    ~Property() override;

    /**
     * Задает свойство для синхронизации значений (биндинг)
     * @param prop синхронизироемое свойство
     */
    void sync(Property<TValue> &prop);

    /**
     * Отменяет синхронизацию
     */
    void unsync();

    /**
     * Возвращает синхронное свойство
     */
    Property<TValue> *getSyncProperty() const;

    /**
     * Задает значение свойства
     */
    Property<TValue> &operator=(TValue value);

    /**
     * Возвращает значение свойства
     */
    operator TValue &() const;  // NOLINT

    /**
     * Обращается к членам типа TValue
     */
    TValue *operator->() const;

protected:
    AProperties *mOwner;
    TValue *mValue;
    Property<TValue> *mSyncProp = nullptr;

    CustomGetterFunc<AProperties, TValue> mGetter = nullptr;
    CustomSetterFunc<AProperties, TValue> mSetter = nullptr;

    /**
     * Задает новое значение через семантику перемещения
     * @param viaSetter использовать пользовательский сеттер (если назначен)?
     * @param value новое значение
     * @param sync true, если синхронизировать со связанным свойством
     */
    void _set(bool viaSetter, TValue &&value, bool sync);

    /**
     * Возвращает значение свойства
     * @param viaGetter использовать пользовательский геттер (если назначен)?
     */
    TValue *_get(bool viaGetter) const;
};

template<class TValue>
Property<TValue>::Property() {
    mValue = new TValue();
}

template<class TValue>
Property<TValue>::Property(TValue &&defValue) : Property() {
    mValue = new TValue(defValue);
}

template<class TValue>
Property<TValue>::~Property() {
    unsync();
}

template<class TValue>
void Property<TValue>::sync(Property<TValue> &prop) {
    if (mSyncProp == nullptr) {
        this->mSyncProp = &prop;
        prop.mSyncProp = this;
        prop._set(true, std::move(*(this->_get(true))), false);
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
Property<TValue> *Property<TValue>::getSyncProperty() const {
    return mSyncProp;
}

template<class TValue>
void Property<TValue>::_set(bool viaSetter, TValue &&value, bool sync) {
    if (*mValue != value) {
        if (viaSetter && mSetter != nullptr)
            (mOwner->*mSetter)(value);
        else
            *mValue = value;
    }

    if (sync && mSyncProp != nullptr)
        mSyncProp->_set(true, std::move(*(_get(true))), false);
}

template<class TValue>
TValue *Property<TValue>::_get(bool viaGetter) const {
    if (viaGetter && mGetter != nullptr)
        return &(mOwner->*mGetter)();
    return mValue;
}

template<class TValue>
Property<TValue> &Property<TValue>::operator=(TValue value) {
    _set(true, std::move(value), true);
    return *this;
}

template<class TValue>
Property<TValue>::operator TValue &() const {
    return *(_get(true));
}

template<class TValue>
TValue *Property<TValue>::operator->() const {
    return _get(true);
}

}

