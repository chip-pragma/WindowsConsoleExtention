#pragma once

#include <string>
#include <iostream>

#include "cpe/core/terminal.h"
#include "ReaderAbstract.h"
#include "cpe/ui/element/ElementInterface.h"
#include "cpe/ui/BufferManip.h"

namespace cpe {

class LineReader : public ElementInterface, public ReaderAbstract<std::string> {
public:
    void run(ControllerInterface &controller, Buffer &out) override;
};

}

