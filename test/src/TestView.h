#pragma once

#include <cpe/ui/view/BaseView.h>
#include <cpe/ui/writer/Notification.h>
#include <cpe/ui/reader/LineReader.h>

#include "TestController.h"

class TestView : public cpe::BaseView<TestController> {
    using BaseClass = cpe::BaseView<TestController>;
public:
    ~TestView() override { };

protected:
    void on_initialize() override;
};


