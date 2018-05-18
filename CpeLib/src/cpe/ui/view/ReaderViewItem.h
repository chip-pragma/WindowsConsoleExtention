#pragma once

#include <iostream>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/reader/IReader.h"
#include "cpe/ui/reader/IResultRead.h"
#include "ViewItemBase.h"
#include "cpe/ui/IController.h"

namespace cpe {

template<class TReader, class TInitializer, class TResult>
class ReaderViewItem : public ViewItemBase<TReader, TInitializer> {

public:
    using BaseClass = ViewItemBase<TReader, TInitializer>;
    using ResultClass = TResult;
    template<class TController>
    using ResultReceiverFunc = void (TController::*)(TResult &);

    explicit ReaderViewItem(TReader &reader);

    ~ReaderViewItem() override { };

    template<class TController>
    void assign_result_func(ResultReceiverFunc<TController> resultFunc);

    void run(IController &ctrl);

protected:
    using _PureResultReceiverFunc = void (IController::*)(TResult &);

    TReader &mReader;
    _PureResultReceiverFunc mResultFunc;
};

template<class TReader, class TInitializer, class TResult>
ReaderViewItem<TReader, TInitializer, TResult>::ReaderViewItem(TReader &reader)
        : ViewItemBase<TReader, TInitializer>(reader),
          mReader(reader) {
    static_assert(std::is_base_of<IReader, TReader>::value);
    static_assert(std::is_base_of<IResultRead, TResult>::value);
}

template<class TReader, class TInitializer, class TResult>
template<class TController>
void ReaderViewItem<TReader, TInitializer, TResult>::assign_result_func(ResultReceiverFunc<TController> resultFunc) {
    mResultFunc = static_cast<_PureResultReceiverFunc>(resultFunc);
}

template<class TReader, class TInitializer, class TResult>
void ReaderViewItem<TReader, TInitializer, TResult>::run(IController &ctrl) {
    TInitializer initializer(mReader);
    if (BaseClass::mInitFunc)
        (ctrl.*BaseClass::mInitFunc)(initializer);

    while (true) {
        TResult result;
        mReader.read();
        // TODO Заполнить result
        if (mResultFunc)
            (ctrl.*mResultFunc)(result);
        if (static_cast<IResultRead *>(&result)->is_valid())
            break;
    }
}

}



