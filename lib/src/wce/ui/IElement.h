#pragma once

namespace wce {

class BaseScript;

class IElement {
    friend class BaseScript;

public:
    bool visible = true;
    bool waitAnyKey = false;

    virtual~IElement() { };

protected:
    virtual void run(BaseScript &script) = 0;

    virtual void onBeforeRun() = 0;

    virtual void onAfterRun() = 0;
};

}




