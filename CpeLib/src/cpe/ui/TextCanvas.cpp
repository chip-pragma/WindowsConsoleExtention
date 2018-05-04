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
    auto newPos = pos;
    mPrintCursor.position = moveCursor(newPos - mPrintCursor.position);
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
    for (char c : str) {
        mLines.push_back(_StyledChar(mPrintCursor.fore, mPrintCursor.back, c));
    }
}

TextCanvas &TextCanvas::print(const TextCanvas &buffer) {
    mLines.push_back(_Symbol(&buffer));
}

void TextCanvas::outputTo(std::basic_ostream<char> &outStream) const {
    bool useAutoFlush = outStream.flags() & std::ios_base::unitbuf;
    if (useAutoFlush)
        outStream << std::nounitbuf;

    const auto srcForeCol = term::foreground();
    const auto srcBackCol = term::background();

    std::vector<_StyledChar> resultChars;

    // TODO Основная логика вывода

    for (auto c : resultChars) {
        if (c.fore) term::foreground(*c.fore);
        else term::foreground(srcForeCol);
        if (c.back) term::background(*c.back);
        else term::background(srcBackCol);
        outStream << c.character;
    }
    outStream.flush();

    term::foreground(srcForeCol);
    term::background(srcBackCol);

    if (useAutoFlush)
        outStream << std::unitbuf;
}


void TextCanvas::clear() {
    mLines.clear();
}

const Point &TextCanvas::moveCursor(const Point &vector) {
    mPrintCursor.position += vector;

    // TODO расчет позиции курсора в прямоугольнике "Текстового холста"

    mPrintCursor.position.y += mPrintCursor.position.x / mMaxSize.x;
    mPrintCursor.position.x %= mMaxSize.x;

    if (mPrintCursor.position.x < 0)
        mPrintCursor.position.x += mMaxSize.x;

    if (mPrintCursor.position.y < 0) {
        mPrintCursor.position.y = 0;
    }
    if (mPrintCursor.position.y >= mMaxSize.y) {
        mPrintCursor.position.y = mMaxSize.y - 1s;
    }

    while (mPrintCursor.position.y >= mLines.size())
        mLines.push_back(new _StyledChar[mMaxSize.x]);

    return mPrintCursor.position;
}

TextCanvas &TextCanvas::operator<<(const std::string &str) {
    return print(str);
}

TextCanvas &TextCanvas::operator<<(const TextCanvas &buf) {
    // Исключение рекурсии
    if (&buf != this)
        print(buf);
    return *this;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const TextCanvas &buffer) {
    buffer.outputTo(stream);
}

}