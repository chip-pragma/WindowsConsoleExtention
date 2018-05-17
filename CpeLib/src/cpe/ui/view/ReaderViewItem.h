#pragma once

#include <iostream>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/reader/IReader.h"
#include "cpe/ui/IResultRead.h"
#include "ViewItemBase.h"

namespace cpe {

template<class TController, class TReader, class TInitializer, class TResult>
class ReaderViewItem : public ViewItemBase<TController, TInitializer> {
public:
    using ReaderClass = TReader;
    using ResultClass = TResult;
    using ResultReceiverFunc = void (TController::*)(TResult &);

    explicit ReaderViewItem(TReader &reader,
                            InitializerReceiverFunc initFunc = nullptr,
                            ResultReceiverFunc resultFunc = nullptr);

    void run(IController &ctrl);

protected:
    IReader &mReader;
    ResultReceiverFunc mResultFunc;
};

template<class TController, class TReader, class TInitializer, class TResult>
ReaderViewItem<TController, TReader, TInitializer, TResult>::ReaderViewItem(TReader &reader,
                                                                            InitializerReceiverFunc initFunc,
                                                                            ResultReceiverFunc resultFunc)
        : mReader(static_cast<IReader &>(reader)),
          ViewItemBase(static_cast<ICuiElement &>(reader), initFunc),
          mResultFunc(resultFunc) {
    static_assert(std::is_base_of<IResultRead, TResult>::value);
}

template<class TController, class TReader, class TInitializer, class TResult>
void ReaderViewItem<TController, TReader, TInitializer, TResult>::run(IController &ctrl) {
    TInitializer initializer(mReader);
    if (mInitFunc)
        (ctrl.*mInitFunc)(initializer);

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



