#pragma once

#include <string>

namespace cpe {

class IModel {
public:
    virtual ~IModel() { }

    virtual bool getFieldValue(uint32_t idField, std::string &outField) const = 0;

    virtual std::string toString() const = 0;
};

}




