#pragma once

#include <string>
#include <iostream>

#include "cpe/core/terminal.h"
#include "ReaderAbstract.h"
#include "cpe/ui/element/ElementInterface.h"
#include "cpe/ui/WriterAbstract.h"

namespace cpe {

class LineReader : public ReaderAbstract<std::string>,
                   public WriterAbstract {
public:
    void runRead(ConsoleApplication &app, ControllerAbstract &ctrl) override;
};

}

