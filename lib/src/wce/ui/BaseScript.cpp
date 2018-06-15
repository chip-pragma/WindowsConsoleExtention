#include "BaseScript.h"

#include "wce/ui/output/OutputHelper.h"

namespace wce {

BaseScript::~BaseScript() {
    for (auto e : mElements)
        delete e;
}

void BaseScript::run() {
    term::clear();
    onRun();
    term::clear();
}

void BaseScript::runAppend(bool clearBefore) {
    OutputHelper outHelp;
    outHelp.saveState();
    onRun();
    if (clearBefore)
        outHelp.goBackState();
}

void BaseScript::abort() {
    mAborted = true;
}

bool BaseScript::isAborted() const {
    return mAborted;
}

void BaseScript::onRun() {
    OutputHelper outHelp;
    while (true) {
        outHelp.saveState();
        this->onBeforeRun();

        for (auto item : mElements) {
            if (!item->getVisible())
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


