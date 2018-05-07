#pragma once

#include <cstdint>
#include <iostream>

#include "cpe/core/Exception.h"

namespace cpe {

class ConsoleApplication {
public:
    ConsoleApplication(std::ostream &out, std::istream &in);

    ConsoleApplication(const ConsoleApplication&) = delete;

    ConsoleApplication(ConsoleApplication&&) = delete;

    ~ConsoleApplication();

    std::ostream &getOut();

    std::istream &getIn();

private:
    static bool mExist = false;

    std::ostream &mOut;
    std::istream &mIn;
};

}



