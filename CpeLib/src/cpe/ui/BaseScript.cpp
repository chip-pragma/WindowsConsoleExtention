#include "BaseScript.h"

#include "cpe/ui/output/OutputHelper.h"

namespace cpe {

BaseScript::~BaseScript() {
    for (auto e : mElements) {
        delete e;
    }
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


