#include "OutputHelper.h"
#include "cpe/ui/style/TextColor.h"
#include "cpe/core/draw/Point.h"
#include "cpe/core/Exception.h"

namespace cpe {

void OutputHelper::save_state() {
    mStates.push(term::cursor_position());
}

void OutputHelper::back_state(size_t count) {
    auto width = term::buffer_size().getX();
    for (size_t i = 0; i < count && !mStates.empty(); i++) {
        Point last = mStates.top();
        auto curPos = term::cursor_position();
        auto yDiff = curPos.getY() - last.getY();
        int nback = (width - last.getX()) + width * (yDiff - 1) + curPos.getX();

        term::cursor_position(last);
        std::cout << std::string(static_cast<unsigned int>(nback), ' ');
        term::cursor_position(last);

        mStates.pop();
    }
}

size_t OutputHelper::state_count() const {
    return mStates.size();
}

void OutputHelper::begin_colorized(std::ostream &outStream) {
    if (mOutStream)
        throw cpe::Exception("Output has already begined");
    mOutStream = &outStream;

    mOutputAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (mOutputAutoFlush)
        outStream << std::nounitbuf;

    mOutputFore = term::foreground();
    mOutputBack = term::background();
}

void OutputHelper::end_colorized() {
    reset_colors();

    if (mOutputAutoFlush)
        (*mOutStream) << std::unitbuf;

    mOutStream = nullptr;
}

void OutputHelper::apply_color(const TextColor &color) {
    if (color.foreground()) term::foreground(*color.foreground());
    else term::foreground(mOutputFore);
    if (color.background()) term::background(*color.background());
    else term::background(mOutputBack);
}

void OutputHelper::reset_colors() {
    term::foreground(mOutputFore);
    term::background(mOutputBack);
}

}