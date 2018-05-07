#pragma once

#include "cpe/tool/property/ObserverInterface.h"
#include "cpe/tool/property/ProviderInterface.h"
#include "ConsoleApplication.h"

namespace cpe {

class ControllerAbstract : public ObserverInterface,
                           public ProviderInterface {
public:
    explicit ControllerAbstract(ConsoleApplication& app);

    ~ControllerAbstract() override {};

    ConsoleApplication& getAppContext();

private:
    ConsoleApplication& mAppContext;
};


}




