#include "main.h"

#include <cpe/core/terminal.h>
#include <cpe/ui/style/BorderStyle.h>
#include <cpe/tool/Encoder.h>

#include "common.h"
#include "TestScript.h"

using namespace wce;

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
    BorderStyle::FinalEncoding = Encoder(Encoder::CP866);

    TestScript testScr;
    testScr.run();
}
