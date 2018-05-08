#pragma once

#include <iostream>
#include <stack>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"
#include "cpe/ui/style/TextCharStyle.h"

namespace cpe {

class WriteHelper {
protected:
    void save_state();

    Point back_state();

    void begin_output(std::ostream& outStream) const;

    void end_output() const;

    void apply_style(const TextCharStyle& style) const;

private:
    std::stack<Point> mStates;
    static std::ostream* mOutStream;
    static bool mOutputAutoFlush;
    static Color mOutputFore;
    static Color mOutputBack;
};

}




