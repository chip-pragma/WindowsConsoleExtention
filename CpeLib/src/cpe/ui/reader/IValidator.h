#pragma once

#include <vector>
#include <string>

namespace cpe {

template<class TValue>
class IValidator {
public:
    virtual ~IValidator() { }

    virtual void validate(const TValue &value, std::vector<std::string> &outErrors) const = 0;
};

}



