#include "BaseReaderData.h"

namespace cpe {

BaseReaderData::~BaseReaderData() { }

const TextColor &BaseReaderData::read_color() const {
    return mReadStyle;
}

TextColor &BaseReaderData::read_color() {
    return mReadStyle;
}

const std::string &BaseReaderData::convert_fail_text() const {
    return mConvertFailText;
}

std::string &BaseReaderData::convert_fail_text() {
    return mConvertFailText;
}
}



