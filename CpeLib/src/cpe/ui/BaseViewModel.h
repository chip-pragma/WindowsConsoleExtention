#pragma once

#include "IViewModel.h"

namespace cpe {

class BaseViewModel : public IViewModel {
    template <class TViewModel>
    friend class BaseView;
public:
    ~BaseViewModel() override { }

protected:

    void onBeforeShow() override { };

    void onAfterShow() override { };

public:
    bool isAborted() const;

    void abort();

private:
    bool mAborted = false;
};
}




