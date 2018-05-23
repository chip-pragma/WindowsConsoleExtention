#include "BaseWriterData.h"

namespace cpe {

BaseWriterData::BaseWriterData()
        : mWidth(term::buffer_size().x_crd() - 1) {

}

const int32_t &BaseWriterData::width() const {
    return mWidth;
}

int32_t &BaseWriterData::width() {
    return mWidth;
}

}




