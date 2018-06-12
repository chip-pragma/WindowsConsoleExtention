#pragma once

#include <cstdint>

#include "cpe/ui/output/Buffer.h"
#include "cpe/ui/BaseElement.h"

namespace cpe {

template<class TDerived>
class BaseWriter : public BaseElement<TDerived> {
public:
    static const int32_t MAX_HEIGHT = 128;

    BaseWriter();

    ~BaseWriter() override { };

    const int32_t &getWidth() const;

    int32_t &getWidth();

protected:
    int32_t mWidth = term::getBufferSize().getXRef() - 1;

    void run(BaseScript &script) final;

    virtual void onWrite(Buffer &buf) = 0;
};

template<class TDerived>
BaseWriter<TDerived>::BaseWriter() {

}

template<class TDerived>
const int32_t &BaseWriter<TDerived>::getWidth() const {
    return mWidth;
}

template<class TDerived>
int32_t &BaseWriter<TDerived>::getWidth() {
    return mWidth;
}

template<class TDerived>
void BaseWriter<TDerived>::run(BaseScript &script) {
    if (!this->getVisible())
        return;
    this->onBeforeRun();
    this->fireBeforeRun(script);

    Buffer buf(Point(this->getWidth(), MAX_HEIGHT));
    onWrite(buf);
    buf.outputTo(std::cout);

    if (this->isCallPause())
        term::callPause();
    this->onAfterRun();
}


}




