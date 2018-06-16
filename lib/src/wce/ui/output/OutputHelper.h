#pragma once

#include <iostream>
#include <stack>

#include "wce/core/console.h"

namespace wce {

class TextColor;
class Point;

class OutputHelper {
public:
    OutputHelper();

    void saveState();

    void goBackState(size_t count = 1);

    size_t getStateCount() const;

    void beginColorize(std::ostream &outStream);

    void endColorize();

    void applyColor(const TextColor &color);

    void resetColor();

private:
    std::stack<Point> m_states;
    std::ostream *m_outStream = nullptr;
    bool m_outputAutoFlush;
    ColorIndex m_outputFore;
    ColorIndex m_outputBack;
};

}




