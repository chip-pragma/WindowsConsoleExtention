#pragma once

#include "IViewModel.h"

namespace cpe {

class BaseViewModel : public IViewModel {
    template <class TViewModel>
    friend class BaseView;
protected:
    void onBeforeShow() override { };

    void onAfterShow() override { };
};
}




