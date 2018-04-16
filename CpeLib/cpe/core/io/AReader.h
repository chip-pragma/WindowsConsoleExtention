#pragma once

#include <type_traits>
#include <cpe/core/except/Exception.h>

#include "cpe/core/IModel.h"

namespace cpe::core::io {

template<class TValue>
class AReader {
public:
    virtual void bind(TValue &varPointer) final;

    template<class TModel>
    void bind(IModel &obj,
              void(TModel::*setter)(const TValue &),
              const TValue &(TModel::* getter)() const);

    virtual TValue read() const = 0;

protected:
    using IBindableSetter = void (IModel::*)(const TValue &);
    using IBindableGetter = const TValue &(IModel::*)() const;

    TValue *mBindedVar = nullptr;
    IModel *mBindedObj = nullptr;
    IBindableSetter mBindedSetter;
    IBindableGetter mBindedGetter;

    virtual void fireBinded(const TValue &newValue) const final;

    virtual const TValue &getBindedValue(const TValue &defValue) const final;
};

template<class T>
void AReader<T>::bind(T &varPointer) {
    mBindedVar = &varPointer;
    mBindedGetter = nullptr;
    mBindedSetter = nullptr;
}

template<class T>
void AReader<T>::fireBinded(const T &newValue) const {
    if (mBindedVar != nullptr)
        *mBindedVar = newValue;
    else if (mBindedObj != nullptr && mBindedSetter != nullptr)
        (mBindedObj->*mBindedSetter)(newValue);
}

template<class T>
const T &AReader<T>::getBindedValue(const T &defValue) const {
    if (mBindedObj != nullptr && mBindedGetter != nullptr)
        return (mBindedObj->*mBindedGetter)();
    else
        return defValue;
}

template<class TValue>
template<class TIBindableChild>
void AReader<TValue>::bind(
        IModel &obj,
        void (TIBindableChild::*setter)(const TValue &),
        const TValue &(TIBindableChild::*getter)() const) {
    if (!std::is_same<TIBindableChild, IModel>::value)
        throw core::except::Exception();

    mBindedVar = nullptr;
    mBindedObj = &obj;
    mBindedSetter = static_cast<IBindableSetter>(setter);
    mBindedGetter = static_cast<IBindableGetter>(getter);
}


}




