#pragma once

#include <iostream>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/writer/IWriter.h"
#include "ViewItemBase.h"

namespace cpe {

template<class TWriter, class TInitializer>
class WriterViewItem : public ViewItemBase<TWriter, TInitializer> {
public:
    using BaseClass = ViewItemBase<TWriter, TInitializer>;

    explicit WriterViewItem(TWriter &writer);

    ~WriterViewItem() override { }

    void run(IController &ctrl);

protected:
    TWriter &mWriter;
};

template<class TWriter, class TInitializer>
WriterViewItem<TWriter, TInitializer>::WriterViewItem(TWriter &writer)
        : ViewItemBase<TWriter, TInitializer>(writer),
          mWriter(writer) {
    static_assert(std::is_base_of<IWriter, TWriter>::value);
}

template<class TWriter, class TInitializer>
void WriterViewItem<TWriter, TInitializer>::run(IController &ctrl) {
    TInitializer initializer(mWriter);
    if (BaseClass::mInitFunc)
        (ctrl.*BaseClass::mInitFunc)(initializer);

    Buffer buf(term::buffer_size() - 1);
    mWriter.draw(buf);
    buf.output_to(std::cout);
}


}

