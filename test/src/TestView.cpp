#include "TestView.h"

void TestView::on_initialize() {
    auto &notif = add<cpe::Notification>();
    notif.bind_initializer_func(&TestController::init_test_notification);

    auto &reader = add<cpe::LineReader>();
    reader.add_command("siska");
    reader.bind_result_func(&TestController::result_test_reader);
}
