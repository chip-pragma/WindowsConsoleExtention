#pragma once

#include <string>

#include "cpe/ui/ACommand.h"
#include "cpe/ui/property/AProperties.h"

namespace cpe {

class Message : public ACommand, public AProperties {
public:
    Message();

    ~Message() override;

    PropertyRW<std::string> *caption;
    PropertyRW<std::string> *text;

    void run() override;

protected:
    void textSet(const std::string &value);

    const std::string &textGet();
};


}




