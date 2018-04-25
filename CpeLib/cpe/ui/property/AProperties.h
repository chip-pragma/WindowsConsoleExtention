#pragma once

#include <functional>
#include <vector>

#include "cpe/Macros.h"
#include "IProperty.h"
#include "Property.h"

namespace cpe {

/**
 * Базовый класс для реализации работы со свойствами
 */
class AProperties {
public:
    virtual ~AProperties() {};

protected:

    /**
     * Создает свойство
     * @tparam TProperty Тип создаваемого свойства
     * @param prop Создаваемое свойство
     */
    template<class TProperty>
    void propCreate(TProperty *&prop);

    /**
     * Создает свойство и назначает пользовательский сеттер
     * @tparam TProperty Тип создаваемого свойства
     * @tparam TIPropsCommand Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Создаваемое свойство
     */
    template<
            class TProperty,
            class TIPropsCommand,
            class TValue>
    void propCreate(TProperty *&prop,
                    CustomSetterFunc<TIPropsCommand, TValue> setter);

    /**
     * Создает свойство и назначает пользовательский геттер
     * @tparam TProperty Тип создаваемого свойства
     * @tparam TIPropsCommand Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Создаваемое свойство
     */
    template<
            class TProperty,
            class TIPropsCommand,
            class TValue>
    void propCreate(TProperty *&prop,
                    CustomGetterFunc<TIPropsCommand, TValue> getter);

    /**
     * Создает свойство и назначает пользовательский сеттер и геттер
     * @tparam TProperty Тип создаваемого свойства
     * @tparam TIPropsCommand Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Создаваемое свойство
     */
    template<
            class TProperty,
            class TIPropsCommand,
            class TValue>
    void propCreate(TProperty *&prop,
                    CustomSetterFunc<TIPropsCommand, TValue> setter,
                    CustomGetterFunc<TIPropsCommand, TValue> getter);

    /**
     * Назначает пользовательский сеттер для указанного свойства
     * @tparam TProperty Тип свойство
     * @tparam TIPropsCommand Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Свойство для назначения
     * @param setter Указатель на член-функцию TIPropsCommand, которая будет сеттером
     */
    template<
            class TProperty,
            class TIPropsCommand,
            class TValue>
    void propAssign(TProperty *&prop,
                    CustomSetterFunc<TIPropsCommand, TValue> setter);

    /**
     * Назначает пользовательский геттер для указанного свойства
     * @tparam TProperty Тип свойство
     * @tparam TIPropsCommand Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Свойство для назначения
     * @param getter Указатель на член-функцию TIPropsCommand, которая будет геттером
     */
    template<
            class TProperty,
            class TIPropsCommand,
            class TValue>
    void propAssign(TProperty *&prop,
                    CustomGetterFunc<TIPropsCommand, TValue> getter);

    /**
     * Назначает пользовательский сеттер и сеттер для указанного свойства
     * @tparam TProperty Тип свойство
     * @tparam TIPropsCommand Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Свойство для назначения
     * @param setter Указатель на член-функцию TIPropsCommand, которая будет сеттером
     * @param getter Указатель на член-функцию TIPropsCommand, которая будет геттером
     */
    template<
            class TProperty,
            class TIPropsCommand,
            class TValue>
    void propAssign(TProperty *&prop,
                    CustomSetterFunc<TIPropsCommand, TValue> setter,
                    CustomGetterFunc<TIPropsCommand, TValue> getter);

    template<class TValue, class TProperty>
    TValue &propValue(TProperty *&prop);

    template<class TValue, class TProperty>
    void propValue(TProperty *&prop, const TValue &);

    /**
     * Удаляет все созданные свойства
     */
    void destroyProperties();

private:
    // Созданные свойства
    std::vector<IProperty *> mPropertyList;
};

template<class TProperty>
void AProperties::propCreate(TProperty *&prop) {
    CPE__STATIC_CHECK_BASE_CLASS(IProperty, TProperty);

    prop = new TProperty(this);
    mPropertyList.push_back(prop);
}

template<class TProperty, class TIPropsCommand, class TValue>
void AProperties::propCreate(TProperty *&prop, CustomSetterFunc<TIPropsCommand, TValue> setter) {
    propCreate(prop);
    propAssign(prop, setter);
}

template<class TProperty, class TIPropsCommand, class TValue>
void AProperties::propCreate(TProperty *&prop, CustomGetterFunc<TIPropsCommand, TValue> getter) {
    propCreate(prop);
    propAssign(prop, getter);
}

template<class TProperty, class TIPropsCommand, class TValue>
void AProperties::propCreate(TProperty *&prop, CustomSetterFunc<TIPropsCommand, TValue> setter,
                             CustomGetterFunc<TIPropsCommand, TValue> getter) {
    propCreate(prop);
    propAssign(prop, setter, getter);
}

template<
        class TProperty,
        class TIPropsCommand,
        class TValue>
void AProperties::propAssign(TProperty *&prop,
                             CustomSetterFunc<TIPropsCommand, TValue> setter) {
    CPE__STATIC_CHECK_BASE_CLASS(Property<TValue>, TProperty);

    auto aProp = static_cast<Property<TValue> *>(prop);
    aProp->mSetter = static_cast<CustomSetterFunc<AProperties, TValue>>(setter);
}

template<
        class TProperty,
        class TIPropsCommand,
        class TValue>
void AProperties::propAssign(TProperty *&prop,
                             CustomGetterFunc<TIPropsCommand, TValue> getter) {
    CPE__STATIC_CHECK_BASE_CLASS(Property<TValue>, TProperty);

    auto aProp = static_cast<Property<TValue> *>(prop);
    aProp->mGetter = static_cast<CustomGetterFunc<AProperties, TValue>>(getter);
};

template<
        class TProperty,
        class TIPropsCommand,
        class TValue>
void AProperties::propAssign(TProperty *&prop,
                             CustomSetterFunc<TIPropsCommand, TValue> setter,
                             CustomGetterFunc<TIPropsCommand, TValue> getter) {
    CPE__STATIC_CHECK_BASE_CLASS(Property<TValue>, TProperty);

    auto aProp = static_cast<Property<TValue> *>(prop);
    aProp->mSetter = static_cast<CustomSetterFunc<AProperties, TValue>>(setter);
    aProp->mGetter = static_cast<CustomGetterFunc<AProperties, TValue>>(getter);
};

template<class TValue, class TProperty>
TValue &AProperties::propValue(TProperty *&prop) {
    auto aProp = static_cast<Property<TValue> *>(prop);
    return aProp->_get();
}

template<class TValue, class TProperty>
void AProperties::propValue(TProperty *&prop, const TValue &value) {
    auto aProp = static_cast<Property<TValue> *>(prop);
    aProp->_set(value, true);
}

}

#undef __CPE__TO_APROPERTY