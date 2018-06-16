#include "OutputHelper.h"
#include "wce/ui/style/TextColor.h"
#include "wce/core/Point.h"
#include "wce/core/Exception.h"

namespace wce {

OutputHelper::OutputHelper()
    : m_outputFore(console::getForeground()),
      m_outputBack(console::getBackground()) { }

void OutputHelper::saveState() {
    m_states.push(console::getCursorPos());
}

void OutputHelper::goBackState(size_t count) {
    auto width = console::getBufferSize().x;
    for (size_t i = 0; i < count && !m_states.empty(); i++) {
        Point last = m_states.top();
        auto curPos = console::getCursorPos();
        auto yDiff = curPos.y - last.y;
        int nback = (width - last.x) + width * (yDiff - 1) + curPos.x;

        console::setCursorPos(last);
        std::cout << std::string(static_cast<unsigned int>(nback), ' ');
        console::setCursorPos(last);

        m_states.pop();
    }
}

size_t OutputHelper::getStateCount() const {
    return m_states.size();
}

void OutputHelper::beginColorize(std::ostream &outStream) {
    if (m_outStream)
        throw wce::Exception("Output has already begined");
    m_outStream = &outStream;

    m_outputAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (m_outputAutoFlush)
        outStream << std::nounitbuf;

    m_outputFore = console::getForeground();
    m_outputBack = console::getBackground();
}

void OutputHelper::endColorize() {
    resetColor();

    if (m_outputAutoFlush)
        (*m_outStream) << std::unitbuf;

    m_outStream = nullptr;
}

void OutputHelper::applyColor(const TextColor &color) {
    if (color.foreground) console::setForeground(*color.foreground);
    else console::setForeground(m_outputFore);
    if (color.background) console::setBackground(*color.background);
    else console::setBackground(m_outputBack);
}

void OutputHelper::resetColor() {
    console::setForeground(m_outputFore);
    console::setBackground(m_outputBack);
}

}