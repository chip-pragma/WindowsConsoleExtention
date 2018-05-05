#include <ntdef.h>
#include "TextCanvas.h"

namespace cpe {

TextCanvas::TextCanvas(uint16_t maxWidth, uint16_t maxHeight) : mMaxSize(maxWidth, maxHeight) {}

TextCanvas::~TextCanvas() {
    clear();
}

//region pen

void TextCanvas::setPen(const Color &color) {
    delete mPrintCursor.fore;
    mPrintCursor.fore = new Color(color);
}

void TextCanvas::getPen(std::nullptr_t) {
    delete mPrintCursor.fore;
    mPrintCursor.fore = nullptr;
}

const Color &TextCanvas::unsetPen(const Color &defColor) const {
    if (mPrintCursor.fore)
        return *mPrintCursor.fore;
    return defColor;
}

//endregion

//region brush

void TextCanvas::setBrush(const Color &color) {
    delete mPrintCursor.back;
    mPrintCursor.back = new Color(color);
}

void TextCanvas::getBrush(std::nullptr_t) {
    delete mPrintCursor.back;
    mPrintCursor.back = nullptr;
}

const Color &TextCanvas::unsetBrush(const Color &defColor) const {
    if (mPrintCursor.back)
        return *mPrintCursor.back;
    return defColor;
}

//endregion

//region cursor

void TextCanvas::setCursor(const Point &pos) {
    mPrintCursor.position = pos;
    _layoutCursor();
}

const Point &TextCanvas::getCursor() {
    return mPrintCursor.position;
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
            auto sc = tl - mPrintCursor.position.x % tl;
            for (int16_t i = 0; i < sc; i++)
                _printSymbol(' ');
        } else {
            _printSymbol(c);
        }
    }
}

TextCanvas &TextCanvas::print(const TextCanvas &canvas) {
    // Исключение рекурсии
    if (&canvas == this)
        return *this;

    // TODO запись буфера в буфер
}

void TextCanvas::outputTo(std::ostream &outStream) const {
    bool useAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (useAutoFlush)
        outStream << std::nounitbuf;

    const auto srcForeCol = term::foreground();
    const auto srcBackCol = term::background();

    for (int i = 0; i < mActualSize.y; i++) {
        auto line = mLines[i];
        for (int j = 0; j < mActualSize.x; j++) {
            auto c = line[j];
            if (c.fore) term::foreground(*c.fore);
            else term::foreground(srcForeCol);
            if (c.back) term::background(*c.back);
            else term::background(srcBackCol);
            outStream << c.character;
        }
        outStream << std::endl;
    }

    term::foreground(srcForeCol);
    term::background(srcBackCol);

    if (useAutoFlush)
        outStream << std::unitbuf;
}

void TextCanvas::clear() {
    for (auto line : mLines) {
        delete[] line;
    }
    mLines.clear();
    mActualSize = Point();
    mPrintCursor.position = Point();
}

void TextCanvas::moveCursor(const Point &vector) {
    mPrintCursor.position += vector;
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

    auto &sym = mLines[mPrintCursor.position.y][mPrintCursor.position.x++];
    mActualSize.x = _min(_max(mActualSize.x, mPrintCursor.position.x), mMaxSize.x);
    sym.character = c;
    sym.fore = mPrintCursor.fore;
    sym.back = mPrintCursor.back;

    _layoutCursor();
}

void TextCanvas::_newLine() {
    mPrintCursor.position.y++;
    mPrintCursor.position.x = 0;

    _layoutCursor();
}

void TextCanvas::_layoutCursor() {
    mPrintCursor.position.y += mPrintCursor.position.x / mMaxSize.x;
    mPrintCursor.position.x = mPrintCursor.position.x % mMaxSize.x;

    if (mPrintCursor.position.x < 0) {
        mPrintCursor.position.y -= 1;
        mPrintCursor.position.x += mMaxSize.x;
    }

    mPrintCursor.position.y = _max(0, mPrintCursor.position.y);

    mEof = (mPrintCursor.position.y >= mMaxSize.y);

    _addLines();
}

void TextCanvas::_addLines() {
    while (mPrintCursor.position.y >= mLines.size())
        mLines.push_back(new _StyledChar[mMaxSize.x]);

    mActualSize.y = _min(static_cast<int16_t>(mLines.size()), mMaxSize.y);
}

int16_t TextCanvas::_max(const int16_t &v1, const int16_t &v2) const {
    return v1 > v2 ? v1 : v2;
}

int16_t TextCanvas::_min(const int16_t &v1, const int16_t &v2) const {
    return v1 < v2 ? v1 : v2;
}

std::ostream &operator<<(std::ostream &stream, const TextCanvas &buffer) {
    buffer.outputTo(stream);
    return stream;
}

}