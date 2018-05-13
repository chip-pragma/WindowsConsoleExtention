#pragma once

#include <iostream>
#include <stack>

#include "cpe/core/terminal.h"


namespace cpe {

class TextColor;
class Point;

class WriteHelper {
protected:

    void state_save();

    Point state_clear_back();

    void output_begin(std::ostream &outStream) const;

    void output_end() const;

    void output_apply_style(const TextColor &style) const;

    void output_reset_style() const;

private:
    std::stack<Point> mStates;
    static std::ostream* mOutStream;
    static bool mOutputAutoFlush;
    static Color mOutputFore;
    static Color mOutputBack;
};

}




