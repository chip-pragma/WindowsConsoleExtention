#pragma once

namespace cpe {

template<class TValue>
class Property {
public:
    ~Property();

private:
    TValue *_mValue = nullptr;
};

template<class TValue>
Property<TValue>::~Property() {
    delete _mValue;
}

}