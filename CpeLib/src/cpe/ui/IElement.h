#pragma once

namespace cpe {

class BaseScript;

class IElement {
public:
    virtual~IElement() { };

    virtual const bool &getVisible() const = 0;

    virtual void setVisible(bool value) = 0;

    virtual const bool &isCallPause() const = 0;

    virtual void setCallPause(bool value) = 0;

    virtual void run(BaseScript &script) = 0;

protected:
    virtual void onBeforeRun() = 0;

    virtual void onRun() = 0;

    virtual void onAfterRun() = 0;
};

}




