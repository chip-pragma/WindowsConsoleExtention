#pragma once

#include "cpe/ui/property/AProperty.h"

namespace cpe {

/**
 * Свойство для чтения и записи
 * @tparam TValue Тип значения свойства
 */
template<class TValue>
class PropertyRW : AProperty<TValue> {
    friend class cpe::AProperties;

public:
    // Возвращает значение
    const TValue &get();

    // Задает значение
    void set(const TValue &value);

private:
    explicit PropertyRW(AProperties *owner);
};

template<class TValue>
PropertyRW<TValue>::PropertyRW(AProperties *owner) : AProperty<TValue>(owner) {
}

template<class TValue>
const TValue &PropertyRW<TValue>::get() {
    return PropertyRW<TValue>::_get();
}

template<class TValue>
void PropertyRW<TValue>::set(const TValue &value) {
    PropertyRW<TValue>::_set(value);
}

}

