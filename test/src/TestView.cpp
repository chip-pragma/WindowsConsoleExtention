#include "TestView.h"

void TestView::on_initialize() {
    auto &notif = make_element<cpe::Notification>();
    notif.bind_data(&TestController::init_test_notification);
    notif.data().size() = cpe::Point(20, 20);

    auto &reader = make_element<cpe::LineReader>();
    reader.bind_result(&TestController::result_test_reader);
}
