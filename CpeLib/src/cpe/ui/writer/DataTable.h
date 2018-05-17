#pragma once

#include "WriterBase.h"

namespace cpe {

class DataTable : public WriterBase {
public:
    void draw(Buffer &cvs) override;
};

}



