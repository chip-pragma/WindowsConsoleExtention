#pragma once

#include <wce/ui/BaseScript.h>
#include <wce/ui/element/Notification.h>

class TestScript : public wce::BaseScript {
public:
    TestScript();

protected:

    void onBeforeRunNotification(wce::Notification& element);
};


