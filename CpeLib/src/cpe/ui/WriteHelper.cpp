#include "WriteHelper.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "cpe/core/Point.h"
#include "cpe/core/Exception.h"

namespace cpe {

std::ostream* WriteHelper::mOutStream;
bool WriteHelper::mOutputAutoFlush;
Color WriteHelper::mOutputFore;
Color WriteHelper::mOutputBack;

void WriteHelper::state_save() {
    mStates.push(term::cursor_position());
}

Point WriteHelper::state_clear_back() {
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

void WriteHelper::output_begin(std::ostream &outStream) const {
    if (mOutStream)
        throw cpe::Exception("Output has already begined");
    mOutStream = &outStream;

    mOutputAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (mOutputAutoFlush)
        outStream << std::nounitbuf;

    mOutputFore = term::foreground();
    mOutputBack = term::background();
}

void WriteHelper::output_end() const {
    output_reset_style();

    if (mOutputAutoFlush)
        (*mOutStream) << std::unitbuf;

    mOutStream = nullptr;
}

void WriteHelper::output_apply_style(const TextCharStyle &style) const {
    Color tmp;
    if (style.get_foreground().get(tmp)) term::foreground(tmp);
    else term::foreground(mOutputFore);
    if (style.get_background().get(tmp)) term::background(tmp);
    else term::background(mOutputBack);
}

void WriteHelper::output_reset_style() const {
    term::foreground(mOutputFore);
    term::background(mOutputBack);
}

}