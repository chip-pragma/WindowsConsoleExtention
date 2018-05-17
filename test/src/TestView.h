#pragma once

#include <cpe/ui/view/ViewBase.h>
#include <cpe/ui/writer/Notification.h>

#include "TestController.h"

class TestView : public cpe::ViewBase<TestController> {
    cpe::Notification m_nTest;

public:
    void init_items() override;
};


