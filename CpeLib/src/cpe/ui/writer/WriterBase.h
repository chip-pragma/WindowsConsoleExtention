#pragma once

#include "IWriter.h"

namespace cpe {

class WriterBase : public IWriter {
public:
    ~WriterBase() override;

    virtual void output_to(std::ostream &outStream, const Point& size);
};

}




