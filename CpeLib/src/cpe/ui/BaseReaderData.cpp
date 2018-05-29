#include "BaseReaderData.h"

namespace cpe {

BaseReaderData::~BaseReaderData() { }

const TextColor &BaseReaderData::getReadColor() const {
    return mReadStyle;
}

TextColor &BaseReaderData::getColorRead() {
    return mReadStyle;
}

const std::string &BaseReaderData::getErrorText() const {
    return mConvertFailText;
}

std::string &BaseReaderData::getErrorText() {
    return mConvertFailText;
}
}



