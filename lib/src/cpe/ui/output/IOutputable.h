#pragma once

#include <iostream>

namespace cpe {

class IOutputable {
public:
    virtual ~IOutputable() { }

    virtual void outputTo(std::ostream &outStream) const = 0;
};

std::ostream &operator<<(std::ostream &os, const IOutputable &outputable);

}




