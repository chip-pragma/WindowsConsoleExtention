#pragma once

#include <vector>

#include "cpe/ui/output/OutputHelper.h"
#include "IView.h"
#include "cpe/ui/ICuiElement.h"
#include "cpe/ui/IController.h"

namespace cpe {

template<class TController>
class BaseView : public IView {
public:
    using ControllerClass = TController;

    BaseView();

    ~BaseView() override;

    TController &initialize();

    void show(bool beforeClean, bool afterClean) final;

protected:
    void on_initialize() override { };

    void on_show_before() override { };

    void on_show_after() override { };

    template<class TElement>
    TElement &make_element();

private:
    IController *mController = nullptr;
    std::vector<ICuiElement *> mElements;
};

template<class TController>
BaseView<TController>::BaseView() {
    static_assert(std::is_base_of<IController, TController>::value);
}

template<class TController>
BaseView<TController>::~BaseView() {
    for (auto item : mElements)
        delete item;
    delete mController;
}

template<class TController>
TController &BaseView<TController>::initialize() {
    if (!mController) {
        mController = static_cast<IController *>(new TController());
        on_initialize();
    }
    return *(static_cast<TController *>(mController));
}

template<class TController>
void BaseView<TController>::show(bool beforeClean, bool afterClean) {
    if (beforeClean)
        term::clear();

    OutputHelper outHelp;
    if (afterClean)
        outHelp.save_state();
    on_show_before();
    for (ICuiElement *item : mElements)
        item->run(*mController);
    on_show_after();
    if (afterClean)
        outHelp.back_state();
}

template<class TController>
template<class TElement>
TElement &BaseView<TController>::make_element() {
    auto elem = new TElement();
    mElements.push_back(elem);
    return *elem;
}

}