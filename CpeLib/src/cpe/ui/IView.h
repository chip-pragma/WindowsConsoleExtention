#pragma once

namespace cpe {

class IView {
public:
    virtual ~IView() { };

protected:
    virtual void onInitialize() = 0;
};

}




