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
        PropertyRW<cpe::Color> *back;
        PropertyRW<cpe::Color> *fore;
    } style;

    Label();

    ~Label() override;

    PropertyRW<std::string> *text;

    void run() override;

protected:
};


}




