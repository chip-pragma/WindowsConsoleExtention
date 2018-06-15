#include "TestScript.h"

#include "common.h"

#include <cpe/ui/element/Notification.h>

TestScript::TestScript() {
    using namespace cpe;

    {
        auto &notif = makeElement<Notification>();
        notif.setCallPause(true);
        notif.getTextRef().append("ПРОВЕРКА!"_dos);
        notif.addBeforeRunCallback(&TestScript::onBeforeRunNotification);
    }

}

void TestScript::onBeforeRunNotification(cpe::Notification &element) {
    element.getBorderRef().getColorRef().getForeRef() = cpe::Colors::LT_PURPLE;
    this->abort();
}
