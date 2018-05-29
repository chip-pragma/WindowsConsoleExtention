#include "BaseWriterData.h"

namespace cpe {

BaseWriterData::BaseWriterData()
        : mWidth(term::getBufferSize().getX() - 1) {

}

const int32_t &BaseWriterData::getWidth() const {
    return mWidth;
}

int32_t &BaseWriterData::getWidth() {
    return mWidth;
}

}




