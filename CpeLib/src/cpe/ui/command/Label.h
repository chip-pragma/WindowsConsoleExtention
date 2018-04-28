#pragma once

#include <string>
#include <cpe/ui/Buffer.h>

#include "cpe/core/Color.h"
#include "ACommand.h"
#include "cpe/utils/property/AProperties.h"
#include "cpe/utils/property/PropertyRW.h"

namespace cpe {

class Label : public ACommand, public AProperties {
public:
    /**
     * Стиль вывода
     */

    Label();

    ~Label() override;

    PropertyRW<std::string> text;
    PropertyRW<cpe::Color> back;
    PropertyRW<cpe::Color> fore;

    void *run(Buffer &buf, std::vector<AReader *> &readers) override;

protected:

    void textSetter(const std::string &value);
};


}




