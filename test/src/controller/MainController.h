#pragma once

#include <cpe/ui/ControllerAbstract.h>
#include <cpe/ui/property/Property.h>

class MainController : public cpe::ControllerAbstract {
public:
    cpe::Property<std::string> testProperty;

};


