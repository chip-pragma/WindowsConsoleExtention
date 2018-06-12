#pragma once

#include <string>

namespace cpe {

class IModel {
public:
    virtual ~IModel() { }

    virtual bool tryGetFieldValue(uint32_t idField, std::string &outField) const = 0;

    virtual std::string toString() const = 0;
};

}




