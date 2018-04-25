#pragma once

#include "cpe/ui/property/AProperty.h"

namespace cpe {

/**
 * Свойство только для записи
 * @tparam TValue Тип значения свойства
 */
template<class TValue>
class PropertyWO : AProperty<TValue> {
    friend class cpe::AProperties;

public:
    // Задает значение
    void set(const TValue &value) {
        AProperty<TValue>::_set(value);
    }

    // TODO Закончить связку свойств (биндинг)
    // TODO Не компилится из-за неопределения базового класса в PropertyRW

protected:
    explicit PropertyWO(AProperties *owner) : AProperty<TValue>(owner) {}
};

/**
 * Свойство только для чтения
 * @tparam TValue Тип значения свойства
 */
template<class TValue>
class PropertyRO : AProperty<TValue> {
    friend class cpe::AProperties;

public:
    // Возвращает значение
    const TValue &get() {
        return AProperty<TValue>::_get();
    }

protected:
    explicit PropertyRO(AProperties *owner) : AProperty<TValue>(owner) {}
};

/**
 * Свойство для чтения и записи
 * @tparam TValue Тип значения свойства
 */
template<class TValue>
class PropertyRW : public PropertyRO<TValue>, public PropertyWO<TValue> {
    friend class cpe::AProperties;

protected:
    explicit PropertyRW(AProperties *owner) : PropertyWO<TValue>(owner),
                                              PropertyRO<TValue>(owner) {}
};

}

