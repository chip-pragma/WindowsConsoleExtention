#pragma once

#include "IWriter.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/InitializerBindingBase.h"

namespace cpe {

template<class TInitializer>
class WriterBase : public IWriter,
                   public InitializerBindingBase<TInitializer> {
    using _InitBinding = InitializerBindingBase<TInitializer>;
public:
    WriterBase();

    ~WriterBase() override { };

    const Point &size() const;

    Point &size();

    void write(Buffer &buf) override;

    void run(IController &ctrl) override;

    virtual void output_to(std::ostream &outStream);

protected:
    Point mSize = term::buffer_size() - 1;

    virtual TInitializer make_initializer() = 0;
};

template<class TInitializer>
WriterBase<TInitializer>::WriterBase() {
    static_assert(std::is_base_of<IInitializer, TInitializer>::value);
}

template<class TInitializer>
const Point &WriterBase<TInitializer>::size() const {
    return mSize;
}

template<class TInitializer>
Point &WriterBase<TInitializer>::size() {
    return mSize;
}

template<class TInitializer>
void WriterBase<TInitializer>::write(Buffer &buf) {
    on_write(buf);
}

template<class TInitializer>
void WriterBase<TInitializer>::run(IController &ctrl) {
    auto initializer = make_initializer();
    _InitBinding::fire_initializer(ctrl, initializer);
    output_to(std::cout);
}

template<class TInitializer>
void WriterBase<TInitializer>::output_to(std::ostream &outStream) {
    Buffer buf(mSize);
    on_write(buf);
    buf.output_to(outStream);
}

}




