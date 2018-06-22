#include "BaseCallback.h"

namespace wce {

void BaseCallback::invoke() {
    onInvoke();
}

void BaseCallback::operator()() {
    onInvoke();
}

}