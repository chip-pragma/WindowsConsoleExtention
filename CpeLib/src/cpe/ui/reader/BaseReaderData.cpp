#include "BaseReaderData.h"

namespace cpe {

BaseReaderData::~BaseReaderData() { }

const TextColor &BaseReaderData::read_color() const {
    return mReadStyle;
}

TextColor &BaseReaderData::read_color() {
    return mReadStyle;
}

}



