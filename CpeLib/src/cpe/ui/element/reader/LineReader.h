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
    explicit LineReader(ViewInterface &parent, PropertyWriteInterface <std::string> &readInto);

    explicit LineReader(ViewInterface &parent, PropertyWriteInterface <std::string> &readInto, const std::string &hint);

    Buffer & run() override;
};

}

