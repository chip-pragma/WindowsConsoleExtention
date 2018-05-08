#pragma once

#include <cstddef>

namespace cpe {

template<class TValue>
class Nullable {
public:
    using ValueType = TValue;

    Nullable() = default;

    Nullable(const Nullable &n) = delete;

    Nullable(Nullable &&n) = delete;

    explicit Nullable(const ValueType &value);

    ~Nullable();

    void set(const ValueType &value);

    void set(std::nullptr_t);

    void set(const Nullable<ValueType> &nullable);

    bool get(ValueType &outValue) const;

    operator bool() const; // NOLINT

    Nullable<ValueType> &operator=(Nullable<ValueType> &) = delete;

    bool operator==(const Nullable<ValueType> &nval) const;

    bool operator!=(const Nullable<ValueType> &nval) const;

    bool operator==(std::nullptr_t) const;

    bool operator!=(std::nullptr_t) const;

private:
    ValueType *mValue = nullptr;
};

//template<class TValue>
//Nullable<TValue>::Nullable(const Nullable &n) {
//    mValue = new TValue(n.mValue);
//}
//
//template<class TValue>
//Nullable<TValue>::Nullable(Nullable &&n) noexcept {
//    mValue = n.mValue;
//    n.mValue = nullptr;
//}

template<class TValue>
Nullable<TValue>::Nullable(const ValueType &value) {
    mValue = new TValue(value);
}

template<class TValue>
Nullable<TValue>::~Nullable() {
    delete mValue;
}

template<class TValue>
void Nullable<TValue>::set(const ValueType &value) {
    delete mValue;
    mValue = new TValue(value);
}

template<class TValue>
void Nullable<TValue>::set(std::nullptr_t) {
    delete mValue;
    mValue = nullptr;
}

template<class TValue>
void Nullable<TValue>::set(const Nullable<ValueType> &nullable) {
    delete mValue;
    mValue = nullptr;
    if (nullable.mValue)
        mValue = new ValueType(*nullable.mValue);
}

template<class TValue>
bool Nullable<TValue>::get(ValueType &outValue) const {
    if (mValue)
        outValue = *mValue;
    return static_cast<bool>(mValue);
}

template<class TValue>
Nullable<TValue>::operator bool() const {
    return static_cast<bool>(mValue);
}

template<class TValue>
bool Nullable<TValue>::operator==(const Nullable<ValueType> &nval) const {
    return (mValue && nval.mValue && *mValue == *nval.mValue);
}

template<class TValue>
bool Nullable<TValue>::operator!=(const Nullable<ValueType> &nval) const {
    return !(nval == *this);
}

template<class TValue>
bool Nullable<TValue>::operator==(std::nullptr_t) const {
    return !static_cast<bool>(mValue);
}

template<class TValue>
bool Nullable<TValue>::operator!=(std::nullptr_t) const {
    return static_cast<bool>(mValue);
}

}




