#pragma once

#include <string>

namespace cpe {

template <class TValue>
class IConverter {
public:
    IConverter() = default;

    virtual bool convert(const std::string& lineValue, TValue &outValue, std::string& errorText) const = 0;
};

}




