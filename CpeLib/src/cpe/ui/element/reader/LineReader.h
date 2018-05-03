#pragma once

#include <string>
#include <iostream>

#include "cpe/core/terminal.h"
#include "ReaderAbstract.h"
#include "cpe/ui/element/ElementAbstract.h"
#include "cpe/ui/BufferManip.h"

namespace cpe {

class LineReader : public ElementAbstract, public ReaderAbstract<std::string> {
public:
    void run(ControllerInterface &controller) override;
};

}

