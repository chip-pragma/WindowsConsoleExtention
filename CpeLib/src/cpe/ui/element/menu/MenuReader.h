#pragma once

#include "cpe/ui/BaseReader.h"
#include "BaseSetItemsSource.h"

namespace cpe {

class MenuReader : public BaseReader<uint32_t>, public BaseSetItemsSource {
public:
    ~MenuReader() override;

protected:

    bool on_convert(std::string &srcLine, uint32_t &convertedValue) override;
};

}




