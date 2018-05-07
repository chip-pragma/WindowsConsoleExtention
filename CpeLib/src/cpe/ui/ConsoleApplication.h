#pragma once

#include <cstdint>
#include <iostream>

#include "cpe/core/Exception.h"

namespace cpe {

class ConsoleApplication {
public:
    ConsoleApplication(std::basic_ostream &out, std::basic_istream &in);

    ConsoleApplication(const ConsoleApplication&) = delete;

    ConsoleApplication(ConsoleApplication&&) = delete;

    ~ConsoleApplication();

    std::basic_ostream &getOut();

    std::basic_istream &getIn();

private:
    static bool mExist = false;

    std::basic_ostream &mOut;
    std::basic_istream &mIn;
};

}



