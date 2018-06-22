#pragma once

namespace wce {

class BaseCallback {
public:
    virtual void invoke() final;

    virtual void operator()() final;

protected:
    virtual void onInvoke() = 0;
};

}


