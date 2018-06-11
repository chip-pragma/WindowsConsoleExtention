#pragma once

#include <cpe/ui/BaseScript.h>
#include <cpe/ui/element/Notification.h>

class TestScript : public cpe::BaseScript {
public:
    TestScript();

protected:

    void onBeforeRunNotification(cpe::Notification& element);
};


