#pragma once

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Point.h"
#include "cpe/ui/IData.h"

namespace cpe {

class BaseWriterData : public IData {
public:
    ~BaseWriterData() override { };

    const Point &size() const;

    Point &size();

protected:
    Point mSize = term::buffer_size() - 1;
};

}



