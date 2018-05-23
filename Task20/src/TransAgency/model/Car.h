#pragma once

#include <cpe/ui/IModel.h>

class Car : public cpe::IModel {
public:
    enum Fields {

    };

    std::string field_value(uint32_t idField) const override;

    std::string to_string() const override;
};


