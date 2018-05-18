#include "TestView.h"

void TestView::init_items() {
    add_writer<cpe::Notification::Initializer>(
            cuiTestWriter,
            &TestController::init_test_notification);

}
