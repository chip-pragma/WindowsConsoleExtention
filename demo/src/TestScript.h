#pragma once

#include <cpe/ui/BaseScript.h>
#include <cpe/ui/element/Notification.h>

class TestScript : public wce::BaseScript {
public:
    TestScript();

protected:

    void onBeforeRunNotification(wce::Notification& element);
};


