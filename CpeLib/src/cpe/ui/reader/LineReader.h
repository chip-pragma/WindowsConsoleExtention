#pragma once

#include <string>
#include <iostream>

#include "cpe/core/terminal.h"
#include "ReaderAbstract.h"
#include "cpe/ui/element/ElementInterface.h"
#include "cpe/ui/WriterAbstract.h"

namespace cpe {

class LineReader : public ElementInterface,
                   public ReaderAbstract<std::string>,
                   public WriterAbstract {
public:
    void run(ControllerAbstract &controller, TextCanvas &out, ReaderManager &readers) override;
};

}

