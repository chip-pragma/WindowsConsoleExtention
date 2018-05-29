#pragma once

#include <string>

namespace cpe {

class IModel {
public:
    virtual ~IModel() { }

    virtual std::string getFieldValue(uint32_t idField) const = 0;

    virtual std::string toString() const = 0;
};

}




