#include "BaseScript.h"

#include "wce/ui/output/OutputHelper.h"

namespace wce {

BaseScript::~BaseScript() {
    for (auto e : m_elements)
        delete e;
}

void BaseScript::run() {
    console::clear();
    onRun();
    console::clear();
}

void BaseScript::runAppend(bool clearBefore) {
    OutputHelper outHelp;
    outHelp.saveState();
    onRun();
    if (clearBefore)
        outHelp.goBackState();
}

void BaseScript::abort() {
    m_aborted = true;
}

bool BaseScript::isAborted() const {
    return m_aborted;
}

void BaseScript::onRun() {
    OutputHelper outHelp;
    while (true) {
        outHelp.saveState();
        this->onBeforeRun();

        for (auto item : m_elements) {
            if (!item->visible)
                continue;
            item->run(*this);
            if (this->isAborted())
                break;
        }

        this->onAfterRun();
        if (this->isAborted())
            break;
        outHelp.goBackState();
    }
}

}


