#pragma once

#include <list>

#include "PropertyObserverInterface.h"


namespace cpe {

class PropertyObservableAbstract {
public:
    void assignObserver(PropertyObserverInterface &observer);

    void rejectObserver(PropertyObserverInterface &observer);

    void notifyObserver(PropertyInterface &changedProperty);

protected:
    PropertyObserverInterface* mObserver = nullptr;
};

}




