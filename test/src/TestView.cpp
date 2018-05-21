#include "TestView.h"

void TestView::on_initialize() {
    auto &notif = add<cpe::Notification>();
    notif.bind_data(&TestController::init_test_notification);

    auto &reader = add<cpe::LineReader>();
    reader.bind_result_func(&TestController::result_test_reader);
}
