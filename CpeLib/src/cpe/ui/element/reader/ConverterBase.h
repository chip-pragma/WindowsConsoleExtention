#pragma once

#include <string>

namespace cpe {

template <class TValue>
class ConverterBase {
public:
    explicit ConverterBase(std::string errorText);

    virtual bool operator()(const std::string& lineValue, TValue &outValue) const = 0;

    const std::string& get_error_text() const;

protected:
    std::string mErrorText;
};

template<class TValue>
ConverterBase<TValue>::ConverterBase(std::string errorText) {
    mErrorText = errorText;
}

template<class TValue>
const std::string &ConverterBase<TValue>::get_error_text() const {
    return mErrorText;
}

}




