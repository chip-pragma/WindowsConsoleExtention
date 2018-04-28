#pragma once

#include <functional>
#include <vector>

#include "cpe/macros.h"
#include "IProperty.h"
#include "AProperty.h"

namespace cpe {

/**
 * Базовый класс для реализации работы со свойствами
 */
class AProperties {
public:
    virtual ~AProperties() {};

protected:

    /**
     * Назначает пользовательский сеттер для указанного свойства
     * @tparam TProperty Тип свойство
     * @tparam TAProps Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Свойство для назначения
     * @param setter Указатель на член-функцию TAProps, которая будет сеттером
     */
    template<
            class TProperty,
            class TAProps,
            class TValue>
    void propAssign(TProperty &prop,
                    CustomSetterFunc<TAProps, TValue> setter);

    /**
     * Назначает пользовательский геттер для указанного свойства
     * @tparam TProperty Тип свойство
     * @tparam TAProps Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Свойство для назначения
     * @param getter Указатель на член-функцию TAProps, которая будет геттером
     */
    template<
            class TProperty,
            class TAProps,
            class TValue>
    void propAssign(TProperty &prop,
                    CustomGetterFunc<TAProps, TValue> getter);

    /**
     * Назначает пользовательский сеттер и сеттер для указанного свойства
     * @tparam TProperty Тип свойство
     * @tparam TAProps Дочерний тип от AProperties
     * @tparam TValue Тип значения свойства
     * @param prop Свойство для назначения
     * @param setter Указатель на член-функцию TAProps, которая будет сеттером
     * @param getter Указатель на член-функцию TAProps, которая будет геттером
     */
    template<
            class TProperty,
            class TAProps,
            class TValue>
    void propAssign(TProperty &prop,
                    CustomSetterFunc<TAProps, TValue> setter,
                    CustomGetterFunc<TAProps, TValue> getter);

    /**
     * Отменяет пользовательский сеттер
     * @tparam TValue Тип значения свойства
     * @tparam TProperty Тип свойство
     * @param prop Свойство для отмены назначения
     */
    template<class TValue, template<class> class TProperty>
    void propUnsetSetter(TProperty<TValue> &prop);

    /**
     * Отменяет пользовательский геттер
     * @tparam TValue Тип значения свойства
     * @tparam TProperty Тип свойство
     * @param prop Свойство для отмены назначения
     */
    template<class TValue, template<class> class TProperty>
    void propUnsetGetter(TProperty<TValue> &prop);

    /**
     * Отменяет пользовательские сеттер и геттер
     * @tparam TValue Тип значения свойства
     * @tparam TProperty Тип свойство
     * @param prop Свойство для отмены назначения
     */
    template<class TValue, template<class> class TProperty>
    void propUnsetAll(TProperty<TValue> &prop);

    template<class TValue, class TProperty>
    TValue &propValue(TProperty &prop);

    template<class TValue, class TProperty>
    void propValue(TProperty &prop, const TValue &value);

private:
    // Созданные свойства
    std::vector<IProperty *> mPropertyList;
};

template<
        class TProperty,
        class TAProps,
        class TValue>
void AProperties::propAssign(TProperty &prop,
                             CustomSetterFunc<TAProps, TValue> setter) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty);

    prop.mOwner = this;
    prop.mSetter = static_cast<CustomSetterFunc<AProperties, TValue>>(setter);
}

template<
        class TProperty,
        class TAProps,
        class TValue>
void AProperties::propAssign(TProperty &prop,
                             CustomGetterFunc<TAProps, TValue> getter) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty);

    prop.mOwner = this;
    prop.mGetter = static_cast<CustomGetterFunc<AProperties, TValue>>(getter);
};

template<
        class TProperty,
        class TAProps,
        class TValue>
void AProperties::propAssign(TProperty &prop,
                             CustomSetterFunc<TAProps, TValue> setter,
                             CustomGetterFunc<TAProps, TValue> getter) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty);

    prop.mOwner = this;
    prop.mSetter = static_cast<CustomSetterFunc<AProperties, TValue>>(setter);
    prop.mGetter = static_cast<CustomGetterFunc<AProperties, TValue>>(getter);
};

template<class TValue, template<class> class TProperty>
void AProperties::propUnsetSetter(TProperty<TValue> &prop) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty<TValue>);
    prop.mSetter = nullptr;
    if (prop.mGetter == nullptr)
        prop.mOwner = nullptr;
}

template<class TValue, template<class> class TProperty>
void AProperties::propUnsetGetter(TProperty<TValue> &prop) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty<TValue>);
    prop.mGetter = nullptr;
    if (prop.mSetter == nullptr)
        prop.mOwner = nullptr;
}

template<class TValue, template<class> class TProperty>
void AProperties::propUnsetAll(TProperty<TValue> &prop) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty<TValue>);
    prop.mSetter = nullptr;
    prop.mGetter = nullptr;
    prop.mOwner = nullptr;
}

template<class TValue, class TProperty>
TValue &AProperties::propValue(TProperty &prop) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty);
    return *(prop._get(false));
}

template<class TValue, class TProperty>
void AProperties::propValue(TProperty &prop, const TValue &value) {
    CPE_MACROS_StaticCheckBaseClass(AProperty<TValue>, TProperty);
    prop._set(false, value);
}

}