#include "TestScript.h"
#include "common.h"

#include <cpe/ui/command/Label.h>
#include <cpe/ui/command/MessageBox.h>

TestScript::TestScript() {
    auto &proc = processor();
    auto &l1 = add<cpe::Label>();
    l1.text = "Программа управления Транспортным Агенством"_dos;
    l1.style.back = cpe::Colors::BLUE;
    l1.style.fore = cpe::Colors::LT_TEAL;
    l1.text.sync(proc.state);
    auto &m1 = add<cpe::MessageBox>();
    m1.caption.text = "ЗАХАЛОВОКЪ"_dos;
}
