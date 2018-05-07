#include <ntdef.h>
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

Nullable <Color> & TextCanvas::foreground() const {
    return mFore;
}

void TextCanvas::foreground(const Nullable<Color> &fore) {
    mFore = fore;
}

Nullable <Color> & TextCanvas::background() const {
    return mBack;
}

void TextCanvas::background(const Nullable<Color> &back) {
    mBack = back;
}

//region cursor

void TextCanvas::setCursor(const Point &pos) {
    mCursor = pos;
    _layoutCursor();
}

const Point &TextCanvas::getCursor() {
    return mCursor;
}

//endregion

//region format

void TextCanvas::setFormat(const TextFormat &wf) {
    mFormat = wf;
}

const TextFormat &TextCanvas::getFormat() {
    return mFormat;
}

//endregion

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
            auto sc = tl - mCursor.x % tl;
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
            if (c.foreground().get(tmp)) term::foreground(tmp);
            else term::foreground(srcForeCol);
            if (c.background().get(tmp)) term::background(tmp);
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
    mCursor = Point();
}

void TextCanvas::moveCursor(const Point &vector) {
    mCursor += vector;
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

    auto &sym = mLines[mCursor.y][mCursor.x];
    sym.setChar(c);
    sym.foreground(mFore);
    sym.background(mBack);

    mActualSize.x = std::min(std::max(mActualSize.x, ++mCursor.x), mMaxSize.x);
    _layoutCursor();
}

void TextCanvas::_newLine() {
    mCursor.y++;
    mCursor.x = 0;

    _layoutCursor();
}

void TextCanvas::_layoutCursor() {
    mCursor.y += mCursor.x / mMaxSize.x;
    mCursor.x = mCursor.x % mMaxSize.x;

    if (mCursor.x < 0) {
        mCursor.y -= 1;
        mCursor.x += mMaxSize.x;
    }

    mCursor.y = std::max(static_cast<int16_t>(0), mCursor.y);

    mEof = (mCursor.y >= mMaxSize.y);

    _addLines();
}

void TextCanvas::_addLines() {
    while (mCursor.y >= mLines.size())
        mLines.push_back(TextLine(static_cast<TextLine::size_type>(mMaxSize.x)));

    mActualSize.y = std::min(static_cast<int16_t>(mLines.size()), mMaxSize.y);
}

std::ostream &operator<<(std::ostream &stream, const TextCanvas &buffer) {
    buffer.outputTo(stream);
    return stream;
}

}