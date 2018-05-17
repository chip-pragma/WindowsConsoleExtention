#include "TestView.h"

void TestView::init_items() {
    make_item(m_nTest, &TestController::init_test_notification);
}
