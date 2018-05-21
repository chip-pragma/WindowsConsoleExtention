#pragma once

#include "BaseReader.h"

namespace cpe {

class LineReader : public BaseReader<std::string> {
protected:
    bool on_convert(std::string &srcLine, std::string &convertedValue) override;
};

}




