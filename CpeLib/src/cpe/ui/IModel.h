#pragma once

#include <string>

namespace cpe {

class IModel {
public:
    virtual ~IModel() { }

    virtual std::string get_field_value(uint32_t idField) const = 0;
};

}




