#include "TestScript.h"

#include "common.h"

#include <wce/ui/element/Notification.h>

TestScript::TestScript() {
    using namespace wce;

    {
        auto &notif = makeElement<Notification>();
        notif.waitAnyKey = true;
        notif.text.append("ПРОВЕРКА!"_dos);
        notif.addBeforeRunCallback(&TestScript::onBeforeRunNotification);
    }

}

void TestScript::onBeforeRunNotification(wce::Notification &element) {
    element.border.color.foreground = wce::console::cPurpleLt;
    this->abort();
}
