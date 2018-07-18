#pragma once

#include <cstdint>

#include "wce/ui/output/Buffer.h"
#include "wce/ui/BaseElement.h"

namespace wce {

template<class TDerived>
class BaseWriter : public BaseElement<TDerived> {
public:
    static const int32_t MAX_HEIGHT = 128;

    BaseWriter();

    ~BaseWriter() override { };

    const int32_t &getWidth() const;

    void setWidth(int32_t w);

protected:
    int32_t m_width = console::getBufferSize().x - 1;

    void run(BaseScript &script) final;

    virtual void onWrite(Buffer &buf) = 0;
};

template<class TDerived>
BaseWriter<TDerived>::BaseWriter() {

}

template<class TDerived>
const int32_t &BaseWriter<TDerived>::getWidth() const {
    return m_width;
}

template<class TDerived>
void BaseWriter<TDerived>::setWidth(int32_t w) {
    m_width = w;
}

template<class TDerived>
void BaseWriter<TDerived>::run(BaseScript &script) {
    this->onBeforeRun();

    Buffer buf(Point(this->getWidth(), MAX_HEIGHT));
    onWrite(buf);
    buf.outputTo(std::cout);

    if (this->waitAnyKey)
        console::waitAnyKey();
    this->onAfterRun();
}


}




