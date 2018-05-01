#include "PropertyObservableAbstract.h"

namespace cpe {

void PropertyObservableAbstract::assignObserver(PropertyObserverInterface &observer) {
    mObserver = &observer;
}

void PropertyObservableAbstract::rejectObserver(PropertyObserverInterface &observer) {
    mObserver = nullptr;
}

void PropertyObservableAbstract::notifyObserver(PropertyInterface &changedProperty) {
    if (mObserver)
        mObserver->handlePropertyChanged(changedProperty);
}


}



