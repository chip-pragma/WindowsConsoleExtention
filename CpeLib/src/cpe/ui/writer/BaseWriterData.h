#pragma once

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Point.h"
#include "cpe/ui/IElementData.h"

namespace cpe {

class BaseWriterData : public IElementData {
public:
    ~BaseWriterData() override { };

    const Point &size() const;

    Point &size();

protected:
    Point mSize = term::buffer_size() - 1;
};

}



