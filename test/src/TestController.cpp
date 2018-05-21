#include "TestController.h"

#include <iostream>

TestController::~TestController() {

}

void TestController::test_func() const {
    std::cout << "[TestController::test_func]\n";
}

void TestController::init_test_notification(cpe::NotificationInitializer &init) {
    init.message().text() = "Message from [TestController::init_test_notification]";
    init.border().color().foreground() = cpe::Colors::LT_GREEN;
    init.border().style().apply(cpe::BorderStyle::DB_OUT_V);
    init.icon() = cpe::StyledChar('!', {cpe::Colors::BLACK, cpe::Colors::LT_RED});
    init.wait(true);
}

void TestController::result_test_reader(cpe::ResultRead<std::string> &result) {
    if (result.type() == cpe::ResultReadType::COMMAND) {
        if (result.command() == "siska") {
            std::cout << "!!! [BOOBS] !!!/n";
        } else if (result.command() == "exit") {
            result.applied_read(true);
            return;
        }
    } else if (result.type() == cpe::ResultReadType::VALUE) {
        std::cout << "Readed: " << result.value() << "\n";
    } else if (result.type() == cpe::ResultReadType::EMPTY) {
        std::cout << "Empty :-(\n";
    }
    result.applied_read(false);
    cpe::term::pause();
}

