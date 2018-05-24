#pragma once

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Point.h"
#include "cpe/ui/BaseElementData.h"

namespace cpe {

class BaseWriterData : public BaseElementData {
public:
    BaseWriterData();

    ~BaseWriterData() override { };

    const int32_t &width() const;

    int32_t &width();

protected:
    int32_t mWidth;
};

}



