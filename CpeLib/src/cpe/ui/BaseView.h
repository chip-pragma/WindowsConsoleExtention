#pragma once

#include <vector>
#include <algorithm>

#include "cpe/ui/output/OutputHelper.h"
#include "IView.h"
#include "cpe/ui/ICuiElement.h"
#include "cpe/ui/BaseViewModel.h"

namespace cpe {

template<class TViewModel>
class BaseView : public IView {
public:
    using ViewModelClass = TViewModel;

    BaseView();

    ~BaseView() override { };

    virtual void showView(TViewModel &viewModel) final;

    virtual void showDialog(TViewModel &viewModel, bool clearBefore) final;

protected:
    void onInitialize() override = 0;

    template<class TElement>
    void addElement(TElement &element);

private:
    std::vector<ICuiElement *> mElements;

    void onShow(TViewModel &viewModel);
};

template<class TViewModel>
BaseView<TViewModel>::BaseView() {
    static_assert(std::is_base_of<BaseViewModel, TViewModel>::value);
}

template<class TViewModel>
void BaseView<TViewModel>::showView(TViewModel &viewModel) {
    term::clear();
    onShow(viewModel);
    term::clear();
}

template<class TViewModel>
void BaseView<TViewModel>::showDialog(TViewModel &viewModel, bool clearBefore) {
    OutputHelper outHelp;
    outHelp.saveState();
    onShow(viewModel);
    if (clearBefore)
        outHelp.goBackState();
}

template<class TViewModel>
void BaseView<TViewModel>::onShow(TViewModel &viewModel) {
    mElements.clear();
    this->onInitialize();

    OutputHelper outHelp;
    auto &vm = static_cast<BaseViewModel &>(viewModel);
    while (true) {
        outHelp.saveState();
        vm.onBeforeShow();
        for (ICuiElement *item : mElements) {
            item->run(vm);
            if (vm.isAborted())
                break;
        }
        vm.onAfterShow();
        if (vm.isAborted())
            break;
        outHelp.goBackState();
    }
}

template<class TViewModel>
template<class TElement>
void BaseView<TViewModel>::addElement(TElement &element) {
    mElements.push_back(static_cast<ICuiElement *>(&element));
}

}