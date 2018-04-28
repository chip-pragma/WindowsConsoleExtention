#include "TestScript.h"
#include "common.h"

#include <cpe/ui/command/Label.h>
#include <cpe/ui/command/MessageBox.h>

TestScript::TestScript() {
    auto &proc = processor();
    auto &l1 = add<cpe::Label>();
    l1.text("This text from TestScript!"_dos);
    l1.back(cpe::Colors::BLUE);
    l1.fore(cpe::Colors::LT_TEAL);
    l1.text.bind(proc.state);
    auto &m1 = add<cpe::MessageBox>();
    m1.caption.text("ЗАХАЛОВОКЪ"_dos);
}
