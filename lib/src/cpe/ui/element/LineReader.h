#pragma once

#include "cpe/ui/BaseReader.h"

namespace cpe {

class LineReader : public BaseReader<LineReader, std::string> {
protected:
public:
    ~LineReader() override;

protected:

    bool onConvert(std::string &srcLine, std::string &convertedValue) override;
};

}




