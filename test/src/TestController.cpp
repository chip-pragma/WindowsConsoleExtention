#include "TestController.h"

#include <iostream>

TestController::~TestController() {

}

void TestController::test_func() const {
    std::cout << "[TestController::test_func]\n";
}

void TestController::init_test_notification(cpe::NotificationInitializer &init) {
    init.message().text() = "Message from [TestController::init_test_notification]";
    init.border().color().foreground().set(cpe::Colors::LT_GREEN);
    init.icon().set({'!', {cpe::Colors::WHITE, cpe::Colors::RED}});
}

