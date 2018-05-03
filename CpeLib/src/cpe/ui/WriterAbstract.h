#pragma once

#include <iostream>
#include <stack>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"

namespace cpe {

class WriterAbstract {
protected:
    void saveState();

    Point clearBack();

private:
    std::stack<Point> _mStates;
};

}




