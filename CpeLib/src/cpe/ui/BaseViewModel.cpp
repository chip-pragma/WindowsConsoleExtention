#include "BaseViewModel.h"

namespace cpe {

bool BaseViewModel::isAborted() const {
    return mAborted;
}

void BaseViewModel::abort() {
    mAborted = true;
}

}