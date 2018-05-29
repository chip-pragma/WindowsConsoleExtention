#pragma once

#include <iostream>
#include <stack>

#include "cpe/core/terminal.h"


namespace cpe {

class TextColor;
class Point;

class OutputHelper {
public:
    void saveState();

    void goBackState(size_t count = 1);

    size_t getStateCount() const;

    void beginColorize(std::ostream &outStream);

    void endColorize();

    void applyColor(const TextColor &color);

    void resetColor();

private:
    std::stack<Point> mStates;
    std::ostream *mOutStream = nullptr;
    bool mOutputAutoFlush;
    Color mOutputFore;
    Color mOutputBack;
};

}




