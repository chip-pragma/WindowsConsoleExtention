#pragma once

#include <vector>

#include "cpe/ui/output/OutputHelper.h"
#include "IView.h"
#include "IViewItem.h"
#include "ReaderViewItem.h"
#include "WriterViewItem.h"
#include "cpe/ui/IController.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/IResultRead.h"

namespace cpe {

template<class TController>
class ViewBase : public IView {
public:
    using ControllerClass = TController;

    ViewBase();

    ~ViewBase() override;

    virtual TController &create_controller();

    void show(bool beforeClean, bool afterClean) final;

protected:
    virtual void init_items() = 0;

    // TODO допилить функции

    template<class TWriter, class TInitializer>
    void add_item(TWriter &element,
                  WriterViewItem<TController, TWriter, TInitializer>::InitializerReceiverFunc initFunc = nullptr);

    template<class TReader, class TInitializer, class TResult>
    void add_item(TReader &reader,
                  ReaderViewItem<TController, TReader, TInitializer, TResult>::InitializerReceiverFunc initFunc = nullptr,
                  ReaderViewItem<TController, TReader, TInitializer, TResult>::ResultReceiverFunc = nullptr);

private:
    IController *mController = nullptr;
    std::vector<IViewItem *> mItems;
};

template<class TController>
ViewBase<TController>::ViewBase() {
    static_assert(std::is_base_of<IController, TController>::value);
}

template<class TController>
ViewBase<TController>::~ViewBase() {
    for (auto item : mItems)
        delete item;
    delete mController;
}

template<class TController>
TController &ViewBase<TController>::create_controller() {
    if (!mController) {
        mController = static_cast<IController *>(new TController());
        init_items();
    }
    return *(static_cast<TController *>(mController));
}

template<class TController>
void ViewBase<TController>::show(bool beforeClean, bool afterClean) {
    if (beforeClean)
        term::clear();

    OutputHelper outHelp;
    if (afterClean)
        outHelp.save_state();

    for (IViewItem *item : mItems)
        item->run(*mController);

    if (afterClean)
        outHelp.back_state();
}

}