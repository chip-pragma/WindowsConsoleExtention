#include "main.h"
#include "common.h"

#include <wce/core/console.h>
#include <wce/ui/style/BorderStyle.h>
#include <wce/tool/Encoder.h>
#include <wce/core/functional/FunctionDelegate.h>

#include <iostream>

using namespace wce;

int main() {
    console::setTitle("Текст консоли"_dos);
    console::setForeground(console::C_WHITE);
    console::setBackground(console::C_BLACK);

    console::waitAnyKey();
    onTesting();
    console::waitAnyKey();

    return 0;
}

void testFuncToDelegate(int testParam) {
    std::cout << "testParam=" << testParam;
}

void onTesting() {
    BorderStyle::finalEncoding = Encoder(Encoder::CP866);

    auto d = make::delegate(testFuncToDelegate);
    auto d2 = d;
    d(3);
    d(5);
}
