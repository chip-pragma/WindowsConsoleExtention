#pragma once

#include <vector>

#include "cpe/ui/output/OutputHelper.h"
#include "IView.h"
#include "IViewItem.h"
#include "ReaderViewItem.h"
#include "WriterViewItem.h"
#include "cpe/ui/IController.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/reader/IResultRead.h"

namespace cpe {

template<class TController>
class ViewBase : public IView {
public:
    template<class TInitializer>
    using InitializerReceiverFunc = void (TController::*)(TInitializer &);
    template<class TResult>
    using ResultReceiverFunc = void (TController::*)(TResult &);

    using ControllerClass = TController;

    ViewBase();

    ~ViewBase() override;

    virtual TController &initialize();

    void show(bool beforeClean, bool afterClean) final;

protected:
    virtual void init_items() = 0;

    template<class TInitializer, class TWriter, class TItem = WriterViewItem<TWriter, TInitializer>>
    void add_writer(TWriter& writer,
                    InitializerReceiverFunc<TInitializer> initFunc = nullptr);

    template<class TInitializer, class TResult, class TReader, class TItem = ReaderViewItem<TReader, TInitializer, TResult>>
    void add_reader(TReader& reader,
                    InitializerReceiverFunc<TInitializer> initFunc = nullptr,
                    ResultReceiverFunc<TResult> resultFunc = nullptr);

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
TController &ViewBase<TController>::initialize() {
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

template<class TController>
template<class TInitializer, class TWriter, class TItem>
void ViewBase<TController>::add_writer(TWriter &writer,
                                       ViewBase::InitializerReceiverFunc<TInitializer> initFunc) {
    auto item = new TItem(writer);
    item->assign_init_func(initFunc);
    mItems.push_back(static_cast<IViewItem*>(item));
}

template<class TController>
template<class TInitializer, class TResult, class TReader, class TItem>
void ViewBase<TController>::add_reader(TReader &reader,
                                       ViewBase::InitializerReceiverFunc<TInitializer> initFunc,
                                       ViewBase::ResultReceiverFunc<TResult> resultFunc) {
    auto item = new TItem(reader);
    item->assign_init_func(initFunc);
    item->assign_result_func(resultFunc);
    mItems.push_back(static_cast<IViewItem*>(item));
}

}