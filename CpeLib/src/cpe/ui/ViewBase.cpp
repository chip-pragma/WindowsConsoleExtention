#include "ViewBase.h"

namespace cpe {

void ViewBase::show(bool beforeClean, bool afterClean) {
    if (beforeClean)
        term::clear();

    if (afterClean)
        state_save();

    work();

    if (afterClean)
        state_clear_back();
}

}