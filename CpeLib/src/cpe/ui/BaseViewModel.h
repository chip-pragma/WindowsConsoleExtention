#pragma once

#include "IViewModel.h"

namespace cpe {

class BaseViewModel : public IViewModel {
    template <class TViewModel>
    friend class BaseView;
protected:
public:
    ~BaseViewModel() override { }

protected:

    void onBeforeShow() override { };

    void onAfterShow() override { };

    void resetView();
private:
    bool mReset = false;
};
}




