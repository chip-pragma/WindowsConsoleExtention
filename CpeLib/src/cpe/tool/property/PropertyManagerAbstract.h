#pragma once

#include "Property.h"

namespace cpe {

class PropertyManagerAbstract {
protected:
    template<class TValue>
    void propSetToObserver(Property<TValue> &prop, ObserverInterface &observer);

    template<class TValue>
    void propGetFromProvider(Property<TValue> &prop, ProviderInterface &provider);
};

template<class TValue>
void PropertyManagerAbstract::propSetToObserver(Property<TValue> &prop, ObserverInterface &observer) {
    prop._setToObserver(observer);
}

template<class TValue>
void PropertyManagerAbstract::propGetFromProvider(Property<TValue> &prop, ProviderInterface &provider) {
    prop._getFromProvider(provider);
}

}




