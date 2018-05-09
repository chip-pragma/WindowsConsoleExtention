#pragma once

#include <string>
#include <iostream>

#include "cpe/core/terminal.h"
#include "ReaderBase.h"
#include "cpe/ui/element/ElementAbstract.h"
#include "cpe/ui/WriteHelper.h"

namespace cpe {

class LineReader : public ReaderBase<std::string>,
                   public WriteHelper {
public:
    bool read(std::string &outValue) override;
};

}

