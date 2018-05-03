#include "WriterAbstract.h"

namespace cpe {

void WriterAbstract::saveState() {
    _mStates.push(term::cursorPosition());
}

Point WriterAbstract::clearBack() {
    if (_mStates.empty())
        return Point();

    auto &last = _mStates.top();
    auto width = term::windowSize().x;
    auto curPos = term::cursorPosition();
    auto yDiff = curPos.y - last.y;
    int count = (width - last.x) + width * (yDiff - 1) + curPos.x;

    term::cursorPosition(last);
    std::cout << std::string(static_cast<unsigned int>(count), ' ');
    term::cursorPosition(last);

    _mStates.pop();
    return last;
}


}