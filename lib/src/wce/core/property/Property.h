#pragma once

#include "BaseProperty.h"

namespace wce {

template<class TValue>
class Property {
public:
    using ValueType = TValue;

    template<class ...Args>
    explicit Property(Args ...args);

    const TValue &get() const;

    TValue &getRef();

    void set(const TValue &value);

    void set(const Property<TValue> &prop);

    TValue *operator->();



private:
    TValue m_value;
};

template<class TValue>
template<class... Args>
Property<TValue>::Property(Args... args)
    : m_value(args...) {

}

}




