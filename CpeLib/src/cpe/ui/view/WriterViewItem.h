#pragma once

#include <iostream>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/writer/IWriter.h"
#include "ViewItemBase.h"

namespace cpe {

template<class TController, class TWriter, class TInitializer>
class WriterViewItem : public ViewItemBase<TController, TInitializer> {
public:
    using WriterClass = TWriter;

    explicit WriterViewItem(TWriter &writer, InitializerReceiverFunc initFunc = nullptr);

    void run(IController &ctrl);

protected:
    IWriter &mWriter;
};

template<class TController, class TWriter, class TInitializer>
WriterViewItem<TController, TWriter, TInitializer>::WriterViewItem(TWriter &writer,
                                                                   InitializerReceiverFunc initFunc)
        : mWriter(static_cast<IWriter &>(writer)),
          ViewItemBase(static_cast<ICuiElement &>(writer), initFunc) {
}

template<class TController, class TWriter, class TInitializer>
void WriterViewItem<TController, TWriter, TInitializer>::run(IController &ctrl) {
    TInitializer initializer(mWriter);
    if (mInitFunc)
        (ctrl.*mInitFunc)(initializer);

    Buffer buf(term::buffer_size() - 1);
    mWriter.draw(buf);
    buf.output_to(std::cout);
}

}

