#pragma once

#include <cpe/ui/IController.h>
#include <cpe/ui/writer/Notification.h>
#include <cpe/ui/reader/ResultRead.h>

class TestController : public cpe::IController {
public:
    ~TestController() override;

    void test_func() const;

    void init_test_notification(cpe::NotificationData &init);

    void result_test_reader(cpe::ResultRead<std::string> &result);
};


