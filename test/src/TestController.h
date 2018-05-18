#pragma once

#include <cpe/ui/IController.h>
#include <cpe/ui/writer/Notification.h>

class TestController : public cpe::IController {
public:
    ~TestController() override;

    void test_func() const;

    void init_test_notification(cpe::Notification::Initializer &init);
};


