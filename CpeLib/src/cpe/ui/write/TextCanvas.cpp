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

Point &TextCanvas::cursor_position() {
    return mCursorPos;
}

void TextCanvas::cursor_position(const Point &pos) {
    mCursorPos = pos;
    _layout_cursor();
}

TextCharStyle &TextCanvas::cursor_style() {
    return mCursorStyle;
}

void TextCanvas::cursor_style(const TextCharStyle &cursorStyle) {
    mCursorStyle = cursorStyle;
}

void TextCanvas::format(const TextFormat &wf) {
    mFormat = wf;
}

const TextFormat &TextCanvas::format() {
    return mFormat;
}

const Point &TextCanvas::max_size() const {
    return mMaxSize;
}

const Point &TextCanvas::actual_size() const {
    return mActualSize;
}

TextCanvas &TextCanvas::draw(const std::string &str) {
    _add_lines();
    for (char c : str) {
        if (c == '\n' || c == '\r') {
            _new_line();
        } else if (c == '\t') {
            auto tl = format().getTabLength();
            auto sc = tl - mCursorPos.x % tl;
            for (int16_t i = 0; i < sc; i++)
                _print_symbol(' ');
        } else {
            _print_symbol(c);
        }
    }
    return *this;
}

TextCanvas &TextCanvas::draw(const TextCanvas &canvas) {
    // Исключение рекурсии
    if (&canvas == this)
        return *this;


    // TODO запись холста в холст

    return *this;
}

void TextCanvas::output_to(std::ostream &outStream) const {
    output_begin(outStream);
    for (int i = 0; i < mActualSize.y; i++) {
        auto line = mLines[i];
        if (mActualSize.y < mLines.size() &&
            i + 1 == mActualSize.y)
            line.setAsUnfinished(mFormat.getUnfinished());
        for (int j = 0; j < mActualSize.x; j++) {
            auto c = line[j];
            output_apply_style(c.style());
            outStream << c.getChar();
        }
        outStream << std::endl;
    }
    output_end();
}

void TextCanvas::clear() {
    mLines.clear();
    mActualSize = Point();
    mCursorPos = Point();
}

void TextCanvas::move_cursor(const Point &vector) {
    mCursorPos += vector;
    _layout_cursor();
}

TextCanvas &TextCanvas::operator<<(const std::string &str) {
    return draw(str);
}

TextCanvas &TextCanvas::operator<<(const TextCanvas &canvas) {
    return draw(canvas);
}

void TextCanvas::_print_symbol(char c) {
    if (mEof)
        return;

    auto &sym = mLines[mCursorPos.y][mCursorPos.x];
    sym.setChar(c);
    sym.style(mCursorStyle);

    mActualSize.x = std::min(std::max(mActualSize.x, ++mCursorPos.x), mMaxSize.x);
    _layout_cursor();
}

void TextCanvas::_new_line() {
    mCursorPos.y++;
    mCursorPos.x = 0;

    _layout_cursor();
}

void TextCanvas::_layout_cursor() {
    mCursorPos.y += mCursorPos.x / mMaxSize.x;
    mCursorPos.x = mCursorPos.x % mMaxSize.x;

    if (mCursorPos.x < 0) {
        mCursorPos.y -= 1;
        mCursorPos.x += mMaxSize.x;
    }

    mCursorPos.y = std::max(static_cast<int16_t>(0), mCursorPos.y);

    mEof = (mCursorPos.y >= mMaxSize.y);

    _add_lines();
}

void TextCanvas::_add_lines() {
    while (mCursorPos.y >= mLines.size())
        mLines.push_back(TextLine(static_cast<TextLine::size_type>(mMaxSize.x)));

    mActualSize.y = std::min(static_cast<int16_t>(mLines.size()), mMaxSize.y);
}

std::ostream &operator<<(std::ostream &stream, const TextCanvas &buffer) {
    buffer.output_to(stream);
    return stream;
}

}