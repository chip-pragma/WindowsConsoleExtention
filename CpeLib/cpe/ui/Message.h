#pragma once

#include <string>

#include "ACommand.h"
#include "IProperties.h"

namespace cpe {

class Message : public ACommand, public IProperties {
public:
    Message();

    ~Message() override;

    PropertyRW<std::string> *caption;
    PropertyRW<std::string> *text;

    void run() override;

protected:

};


}




