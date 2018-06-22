#pragma once

#include "../Exception.h"
#include "BaseDelegate.h"

namespace wce {

template<class TReturn, class ...TParams>
class FunctionDelegate : public BaseDelegate<TReturn, TParams...> {
public:
    using FuncType = TReturn(*)(TParams...);

    FunctionDelegate() = default;

    explicit FunctionDelegate(FuncType memFunc);

    ~FunctionDelegate() override { }

    TReturn invoke(TParams... params) override;

    void set(FuncType memFunc);

    void unset();

    bool isSet() const override;

private:
    FuncType m_function = nullptr;
};

template<class TReturn, class... TParams>
FunctionDelegate<TReturn, TParams...>::FunctionDelegate(FunctionDelegate::FuncType memFunc) {
    this->set(memFunc);
}

template<class TReturn, class... TParams>
TReturn FunctionDelegate<TReturn, TParams...>::invoke(TParams... params) {
    if (!isSet())
        throw Exception("Delegate is unset");
    return (*m_function)(params...);
}

template<class TReturn, class... TParams>
void FunctionDelegate<TReturn, TParams...>::set(FunctionDelegate::FuncType memFunc) {
    m_function = memFunc;
}

template<class TReturn, class... TParams>
void FunctionDelegate<TReturn, TParams...>::unset() {
    m_function = nullptr;
}

template<class TReturn, class... TParams>
bool FunctionDelegate<TReturn, TParams...>::isSet() const {
    return m_function != nullptr;
}

};


