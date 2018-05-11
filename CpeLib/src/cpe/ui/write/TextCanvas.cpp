#include "TextCanvas.h"
#include "cpe/core/Exception.h"

#include <cstddef>
#include <sstream>

namespace cpe {

TextCanvas::TextCanvas(const Point &maxSize) : mMaxSize(maxSize) {
    if (maxSize.x == 0 || maxSize.y == 0) {
        std::stringstream ss;
        ss << "Invalid max size (X:"
           << maxSize.x << "; Y:" << maxSize.y << ")";
        throw cpe::Exception(ss.str());
    }

    cursor_moving(CURSOR_MOVING_STANDART);
}

TextCanvas::~TextCanvas() {
    clear();
}

const Point &TextCanvas::cursor_position() const {
    return mCursorPos;
}

void TextCanvas::cursor_position(const Point &pos) {
    (*mPtr.curPos1) = pos.x;
    (*mPtr.curPos2) = pos.y;
    _layout_cursor();
}

const TextCharStyle &TextCanvas::cursor_style() const {
    return mCursorStyle;
}

TextCharStyle &TextCanvas::cursor_style() {
    return mCursorStyle;
}

void TextCanvas::cursor_style(const TextCharStyle &cursorStyle) {
    mCursorStyle = cursorStyle;
}

int32_t TextCanvas::cursor_moving() const {
    return mCursorMoving;
}

void TextCanvas::cursor_moving(TextCanvas::CursorMoving cursorMoving) {
    mCursorMoving = cursorMoving;

    if (mCursorMoving & CURSOR_MOVING_VERTICAL) {
        mPtr.curPos1 = &mCursorPos.y;
        mPtr.curPos2 = &mCursorPos.x;
        mPtr.maxSize1 = &mMaxSize.y;
        mPtr.maxSize2 = &mMaxSize.x;
        mPtr.actSize1 = &mActualSize.y;
        mPtr.actSize2 = &mActualSize.x;
        mPtr.iteration1 = &mIteration.y;
        mPtr.iteration2 = &mIteration.x;
    } else {
        mPtr.curPos1 = &mCursorPos.x;
        mPtr.curPos2 = &mCursorPos.y;
        mPtr.maxSize1 = &mMaxSize.x;
        mPtr.maxSize2 = &mMaxSize.y;
        mPtr.actSize1 = &mActualSize.x;
        mPtr.actSize2 = &mActualSize.y;
        mPtr.iteration1 = &mIteration.x;
        mPtr.iteration2 = &mIteration.y;
    }

    if (mCursorMoving & CURSOR_MOVING_NO_WRAP)
        mIteration.y = 0;
    else
        mIteration.y = 1;

    if (mCursorMoving & CURSOR_MOVING_REVERSE)
        mIteration.x = -1;
    else
        mIteration.x = 1;

}

const TextFormat &TextCanvas::format() const {
    return mFormat;
}

TextFormat &TextCanvas::format() {
    return mFormat;
}

void TextCanvas::format(const TextFormat &wf) {
    mFormat = wf;
}

const Point &TextCanvas::max_size() const {
    return mMaxSize;
}

const Point &TextCanvas::actual_size() const {
    return mActualSize;
}

void TextCanvas::draw(const std::string &str) {
    _add_lines();
    for (char c : str) {
        if (c == '\n' || c == '\r') {
            _wrap();
        } else if (c == '\t') {
            auto tl = format().getTabLength();
            auto sc = tl - mCursorPos.x % tl;
            for (int16_t i = 0; i < sc; i++)
                _print_symbol(' ');
        } else {
            _print_symbol(c);
        }
    }
}

void TextCanvas::draw(const TextCanvas &canvas, bool useActualSize) {
    // Исключение рекурсии
    if (&canvas == this)
        return;

    const Point srcCurPos = mCursorPos;
    Point maxSize = mMaxSize - srcCurPos;
    Point usingSize = canvas.mMaxSize;
    if (useActualSize)
        usingSize = canvas.mActualSize;
    const Point size(std::min(maxSize.x, usingSize.x),
                     std::min(maxSize.y, usingSize.y));

    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            mLines[i + srcCurPos.y][j + srcCurPos.x]
                    = canvas.mLines.at(i).at(j);
            cursor_position(Point(srcCurPos.x, srcCurPos.y + i));
        }
    }

    // TODO запись холста в холст
}

void TextCanvas::draw_line(const std::string &str) {
    draw(str + "\n");
}

void TextCanvas::output_to(std::ostream &outStream) const {
    output_begin(outStream);
    for (int i = 0; i < mActualSize.y; i++) {
        auto line = mLines[i];
        if (mActualSize.y < mLines.size() &&
            i + 1 == mActualSize.y)
            line.set_as_unfinished(mFormat.getUnfinished());
        for (int j = 0; j < mActualSize.x; j++) {
            auto c = line[j];
            output_apply_style(c.style());
            outStream << c.character();
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
    (*mPtr.curPos1) += vector.x;
    (*mPtr.curPos2) += vector.y;
    _layout_cursor();
}

void TextCanvas::_print_symbol(char c) {
    if (mEof)
        return;

    auto &sym = mLines[mCursorPos.y][mCursorPos.x];
    sym.character(c);
    sym.style(mCursorStyle);

    (*mPtr.curPos1) += (*mPtr.iteration1);

    (*mPtr.actSize1) = std::clamp(std::max((*mPtr.actSize1), (*mPtr.curPos1)), int16_t(0), (*mPtr.maxSize1));

    _layout_cursor();
}

void TextCanvas::_wrap() {
    if (mCursorMoving & CURSOR_MOVING_REVERSE) {
        (*mPtr.curPos1) = (*mPtr.maxSize1) - int16_t(1);
    } else {
        (*mPtr.curPos1) = 0;
    }

    (*mPtr.curPos2) += (*mPtr.iteration2);

    (*mPtr.actSize2) = std::clamp(std::max((*mPtr.actSize2), (*mPtr.curPos2)), int16_t(0), (*mPtr.maxSize2));

    _layout_cursor();
}

void TextCanvas::_layout_cursor() {
    auto wrap = (*mPtr.curPos1) / (*mPtr.maxSize1);
    (*mPtr.curPos2) += (wrap * (*mPtr.iteration2)) + (*mPtr.iteration2);

    (*mPtr.curPos1) %= (*mPtr.maxSize1);
    if ((*mPtr.curPos1) < 0)
        (*mPtr.curPos1) += (*mPtr.maxSize1);

    (*mPtr.curPos2) %= (*mPtr.maxSize2);
    if ((*mPtr.curPos2) < 0)
        (*mPtr.curPos2) += (*mPtr.maxSize2);

    mEof = ((*mPtr.curPos2) == (*mPtr.maxSize2));

    _add_lines();
}

void TextCanvas::_add_lines() {
    while (mCursorPos.y >= mLines.size())
        mLines.push_back(TextLine(static_cast<TextLine::size_type>(mMaxSize.x)));
}

}