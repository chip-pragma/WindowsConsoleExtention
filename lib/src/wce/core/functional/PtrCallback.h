#pragma once

#include "BaseCallback.h"

namespace wce {

template <class TFunc>
class PtrCallback : public BaseCallback {
public:
    PtrCallback(TFunc func);

protected:
    TFunc m_func;

    void onInvoke() override;
};

template<class TFunc>
void PtrCallback<TFunc>::onInvoke() {
    (m_func*)();
}

}




