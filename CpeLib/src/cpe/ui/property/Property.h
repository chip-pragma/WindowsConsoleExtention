#pragma once

#include <utility>

#include "PropertyInterface.h"
#include "PropertyAbstract.h"
#include "PropertyWriteInterface.h"
#include "PropertyReadInterface.h"

namespace cpe {

template<class TValue>
class Property : public PropertyAbstract<TValue>,
                 public virtual PropertyWriteInterface<TValue>,
                 public virtual PropertyReadInterface<TValue> {
    friend class PropertyProviderAbstract;

public:
    Property();

    explicit Property(const TValue &defValue);

    TValue &operator()() const override;

    void operator()(const TValue &value) override;
};

template<class TValue>
Property<TValue>::Property() : PropertyAbstract<TValue>() {}

template<class TValue>
Property<TValue>::Property(const TValue &defValue) {
    PropertyAbstract<TValue>::mValue = new TValue(defValue);
}

template<class TValue>
TValue &Property<TValue>::operator()() const {
    return *(PropertyAbstract<TValue>::get(true));
}

template<class TValue>
void Property<TValue>::operator()(const TValue &value) {
    PropertyAbstract<TValue>::set(true, &value);
}

}


