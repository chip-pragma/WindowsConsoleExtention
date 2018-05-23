#pragma once

#include <string>

namespace cpe {

class IModel {
public:
    virtual ~IModel() { }

    virtual std::string field_value(uint32_t idField) const = 0;

    virtual std::string to_string() const = 0;
};

}




