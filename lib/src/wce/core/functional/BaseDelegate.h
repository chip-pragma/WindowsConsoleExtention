#pragma once

#include <cstddef>

namespace wce {

template<class TReturn, class ...TParams>
class BaseDelegate {
public:
    virtual ~BaseDelegate() { }

    virtual TReturn invoke(TParams...) = 0;

    TReturn operator()(TParams... params) {
        return invoke(params...);
    }

    virtual bool isSet() const = 0;

    bool operator==(std::nullptr_t) {
        return !isSet();
    }

    bool operator!=(std::nullptr_t) {
        return isSet();
    }

    operator bool() { // NOLINT
        return isSet();
    }

};

}


