#pragma once

#include <string>

#include <cpe/ui/AProcessor.h>
#include <cpe/utils/property/AProperties.h>
#include <cpe/utils/property/BindProperty.h>

class TestProcessor : public cpe::AProcessor,
                      public cpe::AProperties {
public:
    TestProcessor();

    ~TestProcessor() override;

    cpe::BindProperty<std::string> state;

};


