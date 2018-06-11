#include "TestScript.h"

#include "common.h"

#include <cpe/ui/element/Notification.h>

TestScript::TestScript() {
    using namespace cpe;

    {
        auto &notif = makeChild<Notification>();
        notif.setCallPause(true);
        notif.refText().append("ПРОВЕРКА!"_dos);
        notif.addBeforeRunListener(&TestScript::onBeforeRunNotification);
    }

}

void TestScript::onBeforeRunNotification(cpe::Notification &element) {
    element.refBorder().refColor().refFore() = cpe::Colors::LT_PURPLE;
    this->abort();
}
