#pragma once

#include <cpe/ui/view/ViewBase.h>
#include <cpe/ui/writer/Notification.h>
#include <cpe/ui/reader/LineReader.h>

#include "TestController.h"

class TestView : public cpe::ViewBase<TestController> {
    using BaseClass = cpe::ViewBase<TestController>;

    cpe::Notification cuiTestWriter;
    cpe::LineReader cuiTestReader;

public:
    void init_items() override;
};


