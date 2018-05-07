#pragma once

#include <map>
#include <list>
#include <algorithm>
#include <iostream>

#include "cpe/macros.h"
#include "cpe/core/Exception.h"
#include "ViewInterface.h"
#include "ControllerAbstract.h"
#include "WriterAbstract.h"
#include "cpe/ui/element/ElementInterface.h"

namespace cpe {

template<class TController>
class ViewAbstract : public ViewInterface,
                     public WriterAbstract {
public:
    using ControllerType = TController;

    ViewAbstract();

    ~ViewAbstract();

    ControllerType &initialize();

    void run(bool beforeClear, bool afterClear) final;

    const Point &getElementSize() const;

    void setElementSize(const Point &size);

protected:
    template<class TElement>
    TElement &addElement();

    virtual void initElements() = 0;

private:
    ControllerType *mController = nullptr;
    std::vector<ElementInterface *> mElements;
    Point mElemSize;
};

//region [ DEFINITION ]

template<class TController>
ViewAbstract<TController>::ViewAbstract() : mElemSize(100, 150) {
    CPE_MACROS_StaticCheckBaseClass(ControllerAbstract, ControllerType);
}

template<class TController>
ViewAbstract<TController>::~ViewAbstract() {
    for (auto elem : mElements)
        delete elem;
    mElements.clear();
    delete mController;
}

template<class TController>
TController &ViewAbstract<TController>::initialize() {
    if (!mController) {
        mController = new ControllerType();
        initElements();
    }
    return *mController;
}

template<class TController>
void ViewAbstract<TController>::run(bool beforeClear, bool afterClear) {
    if (!mController)
        throw Exception("Controller has not been created");
    if (beforeClear)
        term::clear();

    if (afterClear)
        saveState();

    TextCanvas canvas(mElemSize);
    for (auto elem : mElements) {
        elem->run(*mController);
        canvas.outputTo(std::cout);
    }

    if (afterClear)
        clearBack();
}

template<class TController>
const Point &ViewAbstract<TController>::getElementSize() const {
    return mElemSize;
}

template<class TController>
void ViewAbstract<TController>::setElementSize(const Point &size) {
    mElemSize = size;
}

template<class TController>
template<class TElement>
TElement &ViewAbstract<TController>::addElement() {
    CPE_MACROS_StaticCheckBaseClass(ElementInterface, TElement);

    auto elem = new TElement();
    mElements.push_back(elem);
    return *elem;
}

//endregion

}




