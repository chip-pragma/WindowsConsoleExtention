#pragma once

#include <iostream>
#include <stack>

#include "cpe/core/terminal.h"


namespace cpe {

class TextColor;
class Point;

class OutputHelper {
public:
    void save_state();

    void back_state(size_t count = 1);

    size_t state_count() const;

    void begin_colorized(std::ostream &outStream);

    void end_colorized();

    void apply_color(const TextColor &color);

    void reset_colors();

private:
    std::stack<Point> mStates;
    std::ostream *mOutStream = nullptr;
    bool mOutputAutoFlush;
    Color mOutputFore;
    Color mOutputBack;
};

}




