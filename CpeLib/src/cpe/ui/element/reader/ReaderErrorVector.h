#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "cpe/ui/style/TextCharStyle.h"

namespace cpe {

class ReaderErrorVector : public std::vector<std::string> {
public:
    void output() const;
};

}



