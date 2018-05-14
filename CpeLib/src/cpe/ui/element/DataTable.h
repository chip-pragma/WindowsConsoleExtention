#pragma once

#include "ElementBase.h"

namespace cpe {

class DataTable : public ElementBase {
public:
    void draw(Buffer &cvs) override;
};

}



