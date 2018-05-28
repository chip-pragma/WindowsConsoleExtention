#pragma once

#include "cpe/ui/BaseReader.h"

namespace cpe {

class LineReader : public BaseReader<std::string> {
protected:
public:
    ~LineReader() override;

protected:

    bool on_convert(std::string &srcLine, std::string &convertedValue) override;
};

}




