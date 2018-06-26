#pragma once

#include <cstddef>

namespace wce {

template<class TReturn, class ...TParams>
class BaseDelegate {
public:
    virtual ~BaseDelegate() { }

    virtual TReturn invoke(TParams...) const = 0;

    TReturn operator()(TParams... params) const {
        return invoke(params...);
    }

    virtual bool isSet() const = 0;

    bool operator==(std::nullptr_t) const {
        return !isSet();
    }

    bool operator!=(std::nullptr_t) const {
        return isSet();
    }

    virtual bool operator==(const BaseDelegate<TReturn, TParams...> &rhs) const = 0;

    bool operator!=(const BaseDelegate<TReturn, TParams...> &rhs) const {
        return !this->operator==(rhs);
    }

    operator bool() const{ // NOLINT
        return isSet();
    }

};

}


