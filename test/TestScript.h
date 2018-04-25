#pragma once

#include <cpe/ui/AScript.h>

#include "TestProcessor.h"

class TestScript : public cpe::AScript<TestProcessor> {
public:
    TestScript();

    ~TestScript() override {}
};


