#pragma once

namespace cpe {

class IView {
public:
    virtual ~IView() { };

    virtual void show(bool beforeClean, bool afterClean) = 0;

protected:
    virtual void onInitialize() = 0;
};

}




