#include "main.h"

#include <cpe/core/terminal.h>

#include "common.h"
#include "TestScript.h"

using namespace cpe;

int main() {
    term::setTitle("Текст консоли"_dos);
    term::setForeground(Colors::WHITE);
    term::setBackground(Colors::BLACK);

    term::callPause();

    onTesting();

    term::callPause();

    return 0;
}

void onTesting() {
    TestScript testScr;
    testScr.run();
}
