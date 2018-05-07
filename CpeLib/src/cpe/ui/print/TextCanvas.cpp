#include <cstddef>
#include <sstream>

#include "cpe/core/Exception.h"
#include "TextCanvas.h"

namespace cpe {

TextCanvas::TextCanvas(const Point &maxSize) : mMaxSize(maxSize) {
    if (maxSize.x == 0 || maxSize.y == 0) {
        std::stringstream ss;
        ss << "Invalid max size (X:"
              << maxSize.x << "; Y:" << maxSize.y << ")";
        throw cpe::Exception(ss.str());
    }
}

TextCanvas::~TextCanvas() {
    clear();
}

Point &TextCanvas::cursorPosition() {
    return mCursorPos;
}

void TextCanvas::cursorPosition(const Point &pos) {
    mCursorPos = pos;
    _layoutCursor();
}

TextCharStyle &TextCanvas::cursorStyle() {
    return mCursorStyle;
}

void TextCanvas::cursorStyle(const TextCharStyle &cursorStyle) {
    mCursorStyle = cursorStyle;
}

void TextCanvas::setFormat(const TextFormat &wf) {
    mFormat = wf;
}

const TextFormat &TextCanvas::getFormat() {
    return mFormat;
}

const Point &TextCanvas::getMaxSize() const {
    return mMaxSize;
}

const Point &TextCanvas::getActualSize() const {
    return mActualSize;
}

TextCanvas &TextCanvas::print(const std::string &str) {
    _addLines();
    for (char c : str) {
        if (c == '\n' || c == '\r') {
            _newLine();
        } else if (c == '\t') {
            auto tl = getFormat().getTabLength();
            auto sc = tl - mCursorPos.x % tl;
            for (int16_t i = 0; i < sc; i++)
                _printSymbol(' ');
        } else {
            _printSymbol(c);
        }
    }
    return *this;
}

TextCanvas &TextCanvas::print(const TextCanvas &canvas) {
    // Исключение рекурсии
    if (&canvas == this)
        return *this;


    // TODO запись холста в холст

    return *this;
}

void TextCanvas::outputTo(std::ostream &outStream) const {
    bool useAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (useAutoFlush)
        outStream << std::nounitbuf;

    const auto srcForeCol = term::foreground();
    const auto srcBackCol = term::background();

    Color tmp;
    for (int i = 0; i < mActualSize.y; i++) {
        auto line = mLines[i];

        if (mActualSize.y < mLines.size() &&
            i + 1 == mActualSize.y)
            line.setAsUnfinished(mFormat.getUnfinished());

        for (int j = 0; j < mActualSize.x; j++) {
            auto c = line[j];
            if (c.style().foreground().get(tmp)) term::foreground(tmp);
            else term::foreground(srcForeCol);
            if (c.style().background().get(tmp)) term::background(tmp);
            else term::background(srcBackCol);
            outStream << c.getChar();
        }

        outStream << std::endl;
    }

    term::foreground(srcForeCol);
    term::background(srcBackCol);

    if (useAutoFlush)
        outStream << std::unitbuf;
}

void TextCanvas::clear() {
    mLines.clear();
    mActualSize = Point();
    mCursorPos = Point();
}

void TextCanvas::moveCursor(const Point &vector) {
    mCursorPos += vector;
    _layoutCursor();
}

TextCanvas &TextCanvas::operator<<(const std::string &str) {
    return print(str);
}

TextCanvas &TextCanvas::operator<<(const TextCanvas &canvas) {
    return print(canvas);
}

void TextCanvas::_printSymbol(char c) {
    if (mEof)
        return;

    auto &sym = mLines[mCursorPos.y][mCursorPos.x];
    sym.setChar(c);
    sym.style(mCursorStyle);

    mActualSize.x = std::min(std::max(mActualSize.x, ++mCursorPos.x), mMaxSize.x);
    _layoutCursor();
}

void TextCanvas::_newLine() {
    mCursorPos.y++;
    mCursorPos.x = 0;

    _layoutCursor();
}

void TextCanvas::_layoutCursor() {
    mCursorPos.y += mCursorPos.x / mMaxSize.x;
    mCursorPos.x = mCursorPos.x % mMaxSize.x;

    if (mCursorPos.x < 0) {
        mCursorPos.y -= 1;
        mCursorPos.x += mMaxSize.x;
    }

    mCursorPos.y = std::max(static_cast<int16_t>(0), mCursorPos.y);

    mEof = (mCursorPos.y >= mMaxSize.y);

    _addLines();
}

void TextCanvas::_addLines() {
    while (mCursorPos.y >= mLines.size())
        mLines.push_back(TextLine(static_cast<TextLine::size_type>(mMaxSize.x)));

    mActualSize.y = std::min(static_cast<int16_t>(mLines.size()), mMaxSize.y);
}

std::ostream &operator<<(std::ostream &stream, const TextCanvas &buffer) {
    buffer.outputTo(stream);
    return stream;
}

}