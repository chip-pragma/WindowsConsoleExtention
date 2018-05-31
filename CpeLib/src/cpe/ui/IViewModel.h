#pragma once

namespace cpe {

class IViewModel {
public:
    virtual ~IViewModel() { };

protected:
    virtual void onBeforeShow() = 0;

    virtual void onAfterShow() = 0;
};

}




