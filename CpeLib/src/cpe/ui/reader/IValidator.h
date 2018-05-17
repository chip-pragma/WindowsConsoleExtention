#pragma once

#include <vector>
#include <string>

namespace cpe {

using ReaderErrorVector = std::vector<std::string>;

template<class TValue>
class IValidator {
public:
    virtual ~IValidator() { }

    virtual void validate(const TValue &value, ReaderErrorVector &outErrors) const = 0;
};

}



