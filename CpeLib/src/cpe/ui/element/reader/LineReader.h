#pragma once

#include <string>
#include <iostream>

#include "cpe/core/terminal.h"
#include "ReaderAbstract.h"
#include "cpe/ui/element/ElementAbstract.h"
#include "cpe/ui/WriteHelper.h"

namespace cpe {

class LineReader : public ReaderAbstract<std::string>,
                   public WriteHelper {
public:
    void read(ValueType &valueRead) override;
};

}

