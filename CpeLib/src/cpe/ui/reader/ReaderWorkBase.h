#pragma once

#include "cpe/ui/IWork.h"
#include "Reader.h"

namespace cpe {

template<class TValue>
class ReaderWorkBase {
public:
    explicit ReaderWorkBase(Reader<TValue> &reader) : mReader(reader) { }

protected:
    Reader<TValue> &mReader;
};

}



