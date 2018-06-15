#pragma once

#include "wce/ui/BaseReader.h"

namespace wce {

class LineReader : public BaseReader<LineReader, std::string> {
protected:
public:
    ~LineReader() override;

protected:

    bool onConvert(std::string &srcLine, std::string &convertedValue) override;
};

}




