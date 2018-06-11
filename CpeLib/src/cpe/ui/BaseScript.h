#pragma once

#include <vector>

#include "IElement.h"

namespace cpe {

class BaseScript {
public:
    virtual ~BaseScript() = 0;

    virtual void run() final;

    virtual void runAppend(bool clearBefore) final;

protected:
    template<class TElement, class ...Args>
    TElement &makeChild(Args ...args);

    void abort();

    bool isAborted() const;

    void onRun();

    virtual void onBeforeRun() { };

    virtual void onAfterRun() { };

private:
    std::vector<IElement *> mElements;
    bool mAborted = false;
};

template<class TElement, class ...Args>
TElement &BaseScript::makeChild(Args ...args) {
    auto element = new TElement(args...);
    mElements.push_back(static_cast<IElement *>(element));
    return *element;
}

}



