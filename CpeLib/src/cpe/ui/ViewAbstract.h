#pragma once

#include <map>
#include <list>
#include <algorithm>

#include "ViewInterface.h"
#include "cpe/macros.h"
#include "property/PropertyObserverInterface.h"
#include "property/PropertyInterface.h"
#include "ControllerAbstract.h"
#include "cpe/ui/element/ElementAbstract.h"

namespace cpe {

template<class TController>
class ViewAbstract : public ViewInterface {
public:
    explicit ViewAbstract(ControllerAbstract &controller);

    ~ViewAbstract();

    void handlePropertyChanged(PropertyInterface &changedProperty) override;

    void run() override;

protected:
    TController & controller();

    std::vector<ElementAbstract *> & elements();

    void bind(PropertyInterface &controllerProp,
              PropertyInterface &elementProp);

    void unbind(PropertyInterface &controllerProp,
                PropertyInterface &elementProp);

private:
    TController *_mController = nullptr;
    std::vector<ElementAbstract *> _mElements;
    bool _mChangingPropertyValues = false;
    std::map<PropertyInterface *, std::list<PropertyInterface *> *> _mBindingProps;
};

template<class TController>
ViewAbstract<TController>::ViewAbstract(ControllerAbstract &controller) :
        _mController(&dynamic_cast<TController &>(controller)) {
    CPE_MACROS_StaticCheckBaseClass(ControllerAbstract, TController);
    controller.assignObserver(*this);
}

template<class TController>
ViewAbstract<TController>::~ViewAbstract() {
    for (auto elem : _mElements)
        delete elem;
    _mElements.clear();
}

template<class TController>
void ViewAbstract<TController>::handlePropertyChanged(PropertyInterface &changedProperty) {
    if (!_mChangingPropertyValues) {
        _mChangingPropertyValues = true;

        _mChangingPropertyValues = false;
    }
}

template<class TController>
void ViewAbstract<TController>::run() {
    for (auto elem : _mElements) {
        if (elem)
            elem->run().flush();
    }
}

template<class TController>
TController &ViewAbstract<TController>::controller() {
    return *_mController;
}

template<class TController>
std::vector<ElementAbstract *> &ViewAbstract<TController>::elements() {
    return _mElements;
}

template<class TController>
void ViewAbstract<TController>::bind(PropertyInterface &controllerProp, PropertyInterface &elementProp) {
    if (_mBindingProps.find(&controllerProp) == _mBindingProps.end()) {
        auto list = new std::list<PropertyInterface*>();
        list->push_back(&elementProp);
        _mBindingProps.emplace(&controllerProp, list);
    } else {
        auto list = _mBindingProps[&controllerProp];
        if (std::find(list->cbegin(), list->cend(), &elementProp) == list->cend()) {
            list->push_back(&elementProp);
        }
    }
}

template<class TController>
void ViewAbstract<TController>::unbind(PropertyInterface &controllerProp, PropertyInterface &elementProp) {

}

}




