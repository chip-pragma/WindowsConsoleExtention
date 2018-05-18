#include "TestController.h"

#include <iostream>

TestController::~TestController() {

}

void TestController::test_func() const {
    std::cout << "[TestController::test_func]\n";
}

void TestController::init_test_notification(cpe::Notification::Initializer &init) {
    init.message().text() = "Message from [TestController::init_test_notification]";
    init.border().color().foreground().set(cpe::Colors::LT_GREEN);
    init.border().style().apply(cpe::BorderStyle::DB_OUT_V);
    init.icon().set({'!', {cpe::Colors::WHITE, cpe::Colors::RED}});
    init.wait(true);
}

