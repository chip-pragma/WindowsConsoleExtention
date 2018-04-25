#pragma once

#include <string>

#include "cpe/ui/ACommand.h"
#include "cpe/ui/property/AProperties.h"

namespace cpe {

class Label : public ACommand, public AProperties {
public:
    /**
     * Стиль вывода
     */
    struct {
        Property<cpe::Color> *back;
        Property<cpe::Color> *fore;
    } style;

    Label();

    ~Label() override;

    Property<std::string> *text;

    void run() override;
};


}




