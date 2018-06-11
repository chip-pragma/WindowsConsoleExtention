#pragma once

#include "IWriter.h"
#include "BaseWriterData.h"
#include "cpe/ui/BaseElement.h"

namespace cpe {

template<class TData>
class BaseWriter : public BaseElement<TData>,
                   public IWriter {
    using _BaseCuiElement = BaseElement<TData>;
public:
    static const int32_t MAX_HEIGHT = 128;

    ~BaseWriter() override { };

    void write(Buffer &buf) final;

    void run(IController &ctrl) final;

    virtual void outputTo(std::ostream &outStream);
};

template<class TData>
void BaseWriter<TData>::write(Buffer &buf) {
    onWrite(buf);
}

template<class TData>
void BaseWriter<TData>::run(IController &ctrl) {
    auto &data = static_cast<IElementData &>(_BaseCuiElement::getData());
    if (!data.getVisible())
        return;
    this->onBeforeRun();
    _BaseCuiElement::fireData(ctrl);
    this->onRun();
    outputTo(std::cout);
    if (data.isCallPause())
        term::callPause();
    this->onAfterRun();
}

template<class TData>
void BaseWriter<TData>::outputTo(std::ostream &outStream) {
    Buffer buf(Point(
        static_cast<BaseWriterData &>(_BaseCuiElement::getData()).getWidth(),
            MAX_HEIGHT));
    onWrite(buf);
    buf.outputTo(outStream);
}

}




