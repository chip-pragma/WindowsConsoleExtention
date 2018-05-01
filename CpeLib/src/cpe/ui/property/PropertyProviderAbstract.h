#pragma once

#include <functional>
#include <list>

#include "cpe/macros.h"
#include "PropertyInterface.h"
#include "PropertyAbstract.h"
#include "PropertyObserverInterface.h"

namespace cpe {

class PropertyProviderAbstract {
public:
    virtual ~PropertyProviderAbstract() {};

protected:

    template<
            class TProperty,
            class TPropProvider,
            class TValue>
    void assignHandler(TProperty &toProperty,
                       CustomSetterFunc<TPropProvider, TValue> setter);

    template<
            class TProperty,
            class TPropProvider,
            class TValue>
    void assignHandler(TProperty &toProperty,
                       CustomGetterFunc<TPropProvider, TValue> getter);

    template<
            class TProperty,
            class TPropProvider,
            class TValue>
    void assignHandler(TProperty &toProperty,
                       CustomSetterFunc<TPropProvider, TValue> setter,
                       CustomGetterFunc<TPropProvider, TValue> getter);

    template<class TValue, template<class> class TProperty>
    void rejectSetter(TProperty<TValue> &toProperty);

    template<class TValue, template<class> class TProperty>
    void rejectGetter(TProperty<TValue> &toProperty);

    template<class TValue, template<class> class TProperty>
    void rejectHandlers(TProperty<TValue> &toProperty);

    template<class TValue, class TProperty>
    TValue &propValue(TProperty &prop);

    template<class TValue, class TProperty>
    void propValue(TProperty &prop, const TValue &value);
};

template<
        class TProperty,
        class TPropProvider,
        class TValue>
void PropertyProviderAbstract::assignHandler(TProperty &toProperty,
                                             CustomSetterFunc<TPropProvider, TValue> setter) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty);

    auto p = static_cast<PropertyAbstract<TValue>>(toProperty);
    p.mOwner = this;
    p.mSetter = static_cast<CustomSetterFunc<PropertyProviderAbstract, TValue>>(setter);
}

template<
        class TProperty,
        class TPropProvider,
        class TValue>
void PropertyProviderAbstract::assignHandler(TProperty &toProperty,
                                             CustomGetterFunc<TPropProvider, TValue> getter) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty);
    auto p = static_cast<PropertyAbstract<TValue>>(toProperty);
    p.mOwner = this;
    p.mGetter = static_cast<CustomGetterFunc<PropertyProviderAbstract, TValue>>(getter);
};

template<
        class TProperty,
        class TPropProvider,
        class TValue>
void PropertyProviderAbstract::assignHandler(TProperty &toProperty,
                                             CustomSetterFunc<TPropProvider, TValue> setter,
                                             CustomGetterFunc<TPropProvider, TValue> getter) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty);
    auto p = static_cast<PropertyAbstract<TValue>>(toProperty);
    p.mOwner = this;
    p.mSetter = static_cast<CustomSetterFunc<PropertyProviderAbstract, TValue>>(setter);
    p.mGetter = static_cast<CustomGetterFunc<PropertyProviderAbstract, TValue>>(getter);
};

template<class TValue, template<class> class TProperty>
void PropertyProviderAbstract::rejectSetter(TProperty<TValue> &toProperty) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty<TValue>);
    auto p = static_cast<PropertyAbstract<TValue>>(toProperty);
    p.mSetter = nullptr;
    if (p.mGetter == nullptr)
        p.mOwner = nullptr;
}

template<class TValue, template<class> class TProperty>
void PropertyProviderAbstract::rejectGetter(TProperty<TValue> &toProperty) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty<TValue>);
    auto p = static_cast<PropertyAbstract<TValue>>(toProperty);
    p.mGetter = nullptr;
    if (p.mSetter == nullptr)
        p.mOwner = nullptr;
}

template<class TValue, template<class> class TProperty>
void PropertyProviderAbstract::rejectHandlers(TProperty<TValue> &toProperty) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty<TValue>);
    auto p = static_cast<PropertyAbstract<TValue>>(toProperty);
    p.mSetter = nullptr;
    p.mGetter = nullptr;
    p.mOwner = nullptr;
}

template<class TValue, class TProperty>
TValue &PropertyProviderAbstract::propValue(TProperty &prop) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty);
    auto p = static_cast<PropertyAbstract<TValue>&>(prop);
    return *(p.get(false));
}

template<class TValue, class TProperty>
void PropertyProviderAbstract::propValue(TProperty &prop, const TValue &value) {
    CPE_MACROS_StaticCheckBaseClass(PropertyAbstract<TValue>, TProperty);
    auto p = static_cast<PropertyAbstract<TValue>&>(prop);
    p.set(false, value);
}

}