#pragma once

#include <cstddef>
#include "NullableException.h"

namespace cpe {

template<class TValue>
class Nullable {
public:
    using ValueType = TValue;

    Nullable() = default;

    Nullable(std::nullptr_t);

    Nullable(const TValue &value);

    Nullable(const Nullable &n);

    Nullable(Nullable &&n) noexcept;

    ~Nullable();

    void set(const TValue &value);

    void set(std::nullptr_t);

    void set(const Nullable<TValue> &nullable);

    bool get(TValue &outValue) const;

    const TValue& get() const;

    TValue& get();

    operator bool() const; // NOLINT

    bool operator==(const Nullable<TValue> &nval) const;

    bool operator!=(const Nullable<TValue> &nval) const;

    bool operator==(const TValue &val) const;

    bool operator!=(const TValue &val) const;

    bool operator==(std::nullptr_t) const;

    bool operator!=(std::nullptr_t) const;

    Nullable<TValue> &operator=(Nullable<TValue> &) = delete;

private:
    TValue *mValue = nullptr;
};

template<class TValue>
Nullable<TValue>::Nullable(std::nullptr_t) : Nullable<TValue>() {

}

template<class TValue>
Nullable<TValue>::Nullable(const TValue &value) {
    mValue = new TValue(value);
}

template<class TValue>
Nullable<TValue>::Nullable(const Nullable &n) {
    if (n.mValue)
        mValue = new TValue(*n.mValue);
}

template<class TValue>
Nullable<TValue>::Nullable(Nullable &&n) noexcept {
    mValue = n.mValue;
    n.mValue = nullptr;
}

template<class TValue>
Nullable<TValue>::~Nullable() {
    delete mValue;
}

template<class TValue>
void Nullable<TValue>::set(const TValue &value) {
    delete mValue;
    mValue = new TValue(value);
}

template<class TValue>
void Nullable<TValue>::set(std::nullptr_t) {
    delete mValue;
    mValue = nullptr;
}

template<class TValue>
void Nullable<TValue>::set(const Nullable<TValue> &nullable) {
    delete mValue;
    mValue = nullptr;
    if (nullable.mValue)
        mValue = new TValue(*nullable.mValue);
}

template<class TValue>
bool Nullable<TValue>::get(TValue &outValue) const {
    if (mValue)
        outValue = *mValue;
    return static_cast<bool>(mValue);
}

template<class TValue>
const TValue &Nullable<TValue>::get() const {
    if (!mValue)
        throw NullableException("Nullable-object's value is undefined (nullptr)");
    return *mValue;
}

template<class TValue>
TValue &Nullable<TValue>::get() {
    if (!mValue)
        throw NullableException("Nullable-object's value is undefined (nullptr)");
    return *mValue;
}

template<class TValue>
Nullable<TValue>::operator bool() const {
    return static_cast<bool>(mValue);
}

template<class TValue>
bool Nullable<TValue>::operator==(const Nullable<TValue> &nval) const {
    return (mValue && nval.mValue && *mValue == *nval.mValue);
}

template<class TValue>
bool Nullable<TValue>::operator!=(const Nullable<TValue> &nval) const {
    return !(nval == *this);
}

template<class TValue>
bool Nullable<TValue>::operator==(const TValue &val) const {
    return (mValue != nullptr) &&
           (*mValue == val);
}

template<class TValue>
bool Nullable<TValue>::operator!=(const TValue &val) const {
    return !(val == *this);
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




