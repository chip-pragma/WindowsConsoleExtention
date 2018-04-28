#pragma once

#include <string>

#include <cpe/ui/AProcessor.h>
#include <cpe/utils/property/AProperties.h>

class TestProcessor : public cpe::AProcessor,
                      public cpe::AProperties {
public:
    TestProcessor();

    ~TestProcessor() override;

    cpe::Property<std::string> state;

};


