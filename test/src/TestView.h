#pragma once

#include <cpe/ui/view/ViewBase.h>
#include <cpe/ui/writer/Notification.h>

#include "TestController.h"

class TestView : public cpe::ViewBase<TestController> {
    using BaseClass = cpe::ViewBase<TestController>;

    cpe::Notification cuiTest;

public:
    void init_items() override;
};


