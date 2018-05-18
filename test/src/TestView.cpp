#include "TestView.h"

void TestView::init_items() {
    add_writer<cpe::Notification::Initializer>(
            cuiTest,
            &TestController::init_test_notification);

}
