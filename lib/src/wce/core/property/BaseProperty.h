#pragma once

namespace wce {

// TODO доработать

template <class TValue>
class BaseProperty {
public:
    using ValueType = TValue;

    template<class ...Args>
    explicit BaseProperty(Args ...args);

    static void bind(BaseProperty<TValue> &prop1, BaseProperty<TValue> &prop2);

private:

};

}




