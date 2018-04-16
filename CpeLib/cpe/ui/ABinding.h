#pragma once

#include <type_traits>

#include "IModel.h"
#include "cpe/core/Exception.h"

namespace cpe::ui {

template<class TValue>
class ABinding {
public:
    virtual void bind(TValue &varPointer) final;

    template<class TModel>
    void bind(IModel &obj,
              void(TModel::*setter)(const TValue &),
              const TValue &(TModel::* getter)() const);

protected:
    using FuncSetter = void (IModel::*)(const TValue &);
    using FuncGetter = const TValue &(IModel::*)() const;

    TValue *mVar = nullptr;
    IModel *mObj = nullptr;
    FuncSetter mObjSetter;
    FuncGetter mObjGetter;

    virtual void setBindingValue(const TValue &newValue) const final;

    virtual const TValue &getBindingValue(const TValue &defValue) const final;
};

template<class TValue>
void ABinding<TValue>::bind(TValue &varPointer) {
    mVar = &varPointer;
    mObjGetter = nullptr;
    mObjSetter = nullptr;
}

template<class TValue>
void ABinding<TValue>::setBindingValue(const TValue &newValue) const {
    if (mVar != nullptr)
        *mVar = newValue;
    else if (mObj != nullptr && mObjSetter != nullptr)
        (mObj->*mObjSetter)(newValue);
}

template<class TValue>
const TValue &ABinding<TValue>::getBindingValue(const TValue &defValue) const {
    if (mObj != nullptr && mObjGetter != nullptr)
        return (mObj->*mObjGetter)();
    else
        return defValue;
}

template<class TValue>
template<class TModel>
void ABinding<TValue>::bind(
        IModel &obj,
        void (TModel::*setter)(const TValue &),
        const TValue &(TModel::*getter)() const) {
    if (!std::is_same<TModel, IModel>::value)
        throw core::Exception();

    mVar = nullptr;
    mObj = &obj;
    mObjSetter = static_cast<FuncSetter>(setter);
    mObjGetter = static_cast<FuncGetter>(getter);
}

}
