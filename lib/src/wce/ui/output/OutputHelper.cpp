#include "OutputHelper.h"
#include "wce/ui/style/TextColor.h"
#include "wce/core/draw/Point.h"
#include "wce/core/Exception.h"

namespace wce {

void OutputHelper::saveState() {
    mStates.push(term::getCursorPos());
}

void OutputHelper::goBackState(size_t count) {
    auto width = term::getBufferSize().getXRef();
    for (size_t i = 0; i < count && !mStates.empty(); i++) {
        Point last = mStates.top();
        auto curPos = term::getCursorPos();
        auto yDiff = curPos.getYRef() - last.getYRef();
        int nback = (width - last.getXRef()) + width * (yDiff - 1) + curPos.getXRef();

        term::setCursorPos(last);
        std::cout << std::string(static_cast<unsigned int>(nback), ' ');
        term::setCursorPos(last);

        mStates.pop();
    }
}

size_t OutputHelper::getStateCount() const {
    return mStates.size();
}

void OutputHelper::beginColorize(std::ostream &outStream) {
    if (mOutStream)
        throw wce::Exception("Output has already begined");
    mOutStream = &outStream;

    mOutputAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (mOutputAutoFlush)
        outStream << std::nounitbuf;

    mOutputFore = term::getForeground();
    mOutputBack = term::getBackground();
}

void OutputHelper::endColorize() {
    resetColor();

    if (mOutputAutoFlush)
        (*mOutStream) << std::unitbuf;

    mOutStream = nullptr;
}

void OutputHelper::applyColor(const TextColor &color) {
    if (color.getFore()) term::setForeground(*color.getFore());
    else term::setForeground(mOutputFore);
    if (color.getBack()) term::setBackground(*color.getBack());
    else term::setBackground(mOutputBack);
}

void OutputHelper::resetColor() {
    term::setForeground(mOutputFore);
    term::setBackground(mOutputBack);
}

}