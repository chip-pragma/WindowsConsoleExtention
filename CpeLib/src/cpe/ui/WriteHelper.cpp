#include "cpe/core/Exception.h"
#include "WriteHelper.h"

namespace cpe {

void WriteHelper::save_state() {
    mStates.push(term::cursor_position());
}

Point WriteHelper::back_state() {
    if (mStates.empty())
        return Point();

    auto &last = mStates.top();
    auto width = term::window_size().x;
    auto curPos = term::cursor_position();
    auto yDiff = curPos.y - last.y;
    int count = (width - last.x) + width * (yDiff - 1) + curPos.x;

    term::cursor_position(last);
    std::cout << std::string(static_cast<unsigned int>(count), ' ');
    term::cursor_position(last);

    mStates.pop();
    return last;
}

void WriteHelper::begin_output(std::ostream &outStream) const {
    if (mOutStream)
        throw cpe::Exception("Output has already begined");
    mOutStream = &outStream;

    mOutputAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (mOutputAutoFlush)
        outStream << std::nounitbuf;

    mOutputFore = term::foreground();
    mOutputBack = term::background();
}

void WriteHelper::end_output() const {
    term::foreground(mOutputFore);
    term::background(mOutputBack);

    if (mOutputAutoFlush)
        (*mOutStream) << std::unitbuf;

    mOutStream = nullptr;
}

void WriteHelper::apply_style(const TextCharStyle &style) const {
    Color tmp;
    if (style.foreground().get(tmp)) term::foreground(tmp);
    else term::foreground(mOutputFore);
    if (style.background().get(tmp)) term::background(tmp);
    else term::background(mOutputBack);
}

}