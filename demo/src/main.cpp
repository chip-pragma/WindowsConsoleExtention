#include "main.h"

#include <wce/core/console.h>
#include <wce/ui/style/BorderStyle.h>
#include <wce/tool/Encoder.h>

#include "common.h"

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

void onTesting() {
    BorderStyle::finalEncoding = Encoder(Encoder::CP866);


}
