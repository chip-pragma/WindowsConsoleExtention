#pragma once

#include <vector>
#include <string>

namespace cpe {

using ValidateErrorList = std::vector<std::string>;

template <class TValue>
class IValidator {
public:
    virtual void operator()(const std::string &value, ValidateErrorList &outErrors) const = 0;
};

}



