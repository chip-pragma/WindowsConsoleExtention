#include "OutputHelper.h"
#include "cpe/ui/style/TextColor.h"
#include "cpe/core/draw/Point.h"
#include "cpe/core/Exception.h"

namespace cpe {

void OutputHelper::save_state() {
    mStates.push(term::cursor_position());
}

void OutputHelper::back_state(size_t count) {
    auto width = term::buffer_size().x_crd();
    for (size_t i = 0; i < count && !mStates.empty(); i++) {
        Point last = mStates.top();
        auto curPos = term::cursor_position();
        auto yDiff = curPos.y_crd() - last.y_crd();
        int nback = (width - last.x_crd()) + width * (yDiff - 1) + curPos.x_crd();

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
    Color tmp;
    if (color.foreground().get(tmp)) term::foreground(tmp);
    else term::foreground(mOutputFore);
    if (color.background().get(tmp)) term::background(tmp);
    else term::background(mOutputBack);
}

void OutputHelper::reset_colors() {
    term::foreground(mOutputFore);
    term::background(mOutputBack);
}

}