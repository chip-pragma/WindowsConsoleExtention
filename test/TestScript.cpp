#include "TestScript.h"

#include <cpe/ui/command/Label.h>

TestScript::TestScript() {
    auto proc = processor();
    auto l1 = add<cpe::Label>();
    l1->text->set("Label ");
    l1->style.back->set(cpe::Colors::BLUE);
    l1->style.fore->set(cpe::Colors::LT_TEAL);
    l1->text->sync(proc->state);
    auto l2 = add<cpe::Label>();
    l2->text->set("CREATED!\n");
    l2->style.back->set(cpe::Colors::RED);
    l2->style.fore->set(cpe::Colors::LT_YELLOW);
}
