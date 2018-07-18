#pragma once

#include <cstddef>

namespace wce {

template<class TReturn, class ...TParams>
class BaseDelegate {
public:
    virtual ~BaseDelegate() { }

    virtual TReturn invoke(TParams...) const = 0;

    TReturn operator()(TParams... params) const;

    virtual bool isSet() const = 0;

    bool operator==(std::nullptr_t) const;

    bool operator!=(std::nullptr_t) const;

    virtual bool operator==(const BaseDelegate<TReturn, TParams...> &rhs) const = 0;

    bool operator!=(const BaseDelegate<TReturn, TParams...> &rhs) const;

    operator bool() const; // NOLINT


};

template<class TReturn, class... TParams>
TReturn BaseDelegate<TReturn, TParams...>::operator()(TParams... params) const {
    return invoke(params...);
}

template<class TReturn, class... TParams>
bool BaseDelegate<TReturn, TParams...>::operator==(std::nullptr_t) const {
    return !isSet();
}

template<class TReturn, class... TParams>
bool BaseDelegate<TReturn, TParams...>::operator!=(std::nullptr_t) const {
    return isSet();
}

template<class TReturn, class... TParams>
BaseDelegate<TReturn, TParams...>::operator bool() const {
    return isSet();
}

template<class TReturn, class... TParams>
bool BaseDelegate<TReturn, TParams...>::operator!=(const BaseDelegate<TReturn, TParams...> &rhs) const {
    return !this->operator==(rhs);
}

}


