#include "TextCanvas.h"
#include "cpe/core/Exception.h"

#include <cstddef>
#include <sstream>

namespace cpe {

//region [ CursorMoving ]

bool operator==(const CursorMoving &cm, uint8_t i) {
    return cm == static_cast<CursorMoving>(i);
}

bool operator!=(const CursorMoving &cm, uint8_t i) {
    return !(cm == i);
}

CursorMoving operator&(const CursorMoving &cm1, const CursorMoving &cm2) {
    return static_cast<CursorMoving>(
            static_cast<uint8_t>(cm1) & static_cast<uint8_t>(cm2));
}

CursorMoving operator|(const CursorMoving &cm1, const CursorMoving &cm2) {
    return static_cast<CursorMoving>(
            static_cast<uint8_t>(cm1) | static_cast<uint8_t>(cm2));
}

//endregion

TextCanvas::TextCanvas(const Size &size) {
    _check_size(size);
    mSize = size;

    mMatrix = new TextCharStyle*[size.height()];
    for (int i = 0; i < size.height(); i++)
        mMatrix[i] = new TextCharStyle[size.width()];
}

TextCanvas::~TextCanvas() {
    if (!mParent) {
        for (int i = 0; i < mSize.mY; i++)
            delete[] mMatrix[i];
        delete[] mMatrix;
    }
}

const Point &TextCanvas::cursor_position() const {
    return mCursorPos;
}

void TextCanvas::cursor_position(const Point &pos) {
    mCursorPos = pos;
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

const TextFormat &TextCanvas::format() const {
    return mFormat;
}

TextFormat &TextCanvas::format() {
    return mFormat;
}

void TextCanvas::format(const TextFormat &wf) {
    mFormat = wf;
}

const Size & TextCanvas::size() const {
    return mSize;
}

const Size & TextCanvas::used_size() const {
    return mUsedSize;
}

bool TextCanvas::have_parent() const {
    return static_cast<bool>(mParent);
}

const TextCanvas &TextCanvas::get_parent() const {
    if (!mParent)
        throw Exception("TextCanvas does not have parent");
    return *mParent;
}

TextCanvas &TextCanvas::get_parent() {
    if (!mParent)
        throw Exception("TextCanvas does not have parent");
    return *mParent;
}

TextCanvas TextCanvas::extract(const Point &begin, const Point &size) {
//    if ()
//
//    TextCanvas ntc(this);
//
//    ntc
//
//    return ntc;
}

void TextCanvas::draw(const std::string &str) {
    _add_lines();
    for (char c : str) {
        if (c == '\n' || c == '\r') {
            _wrap();
        } else if (c == '\t') {
            auto tl = format().getTabLength();
            auto sc = tl - mCursorPos.mX % tl;
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
    Point maxSize = mSize - srcCurPos;
    Point usingSize = canvas.mSize;
    if (useActualSize)
        usingSize = canvas.mUsedSize;
    const Point size(std::min(maxSize.mX, usingSize.mX),
                     std::min(maxSize.mY, usingSize.mY));

    for (int i = 0; i < size.mY; i++) {
        for (int j = 0; j < size.mX; j++) {
            mMatrix[i + srcCurPos.mY][j + srcCurPos.mX]
                    = canvas.mMatrix.at(i).at(j);
            cursor_position(Point(srcCurPos.mX, srcCurPos.mY + i));
        }
    }

    // TODO запись холста в холст
}

void TextCanvas::draw(char character, const CursorMoving &moving) {

}

void TextCanvas::output_to(std::ostream &outStream) const {
    output_begin(outStream);
    for (int i = 0; i < mUsedSize.mY; i++) {
        auto line = mMatrix[i];
        if (mUsedSize.mY < mMatrix.size() &&
            i + 1 == mUsedSize.mY)
            line.set_as_unfinished(mFormat.getUnfinished());
        for (int j = 0; j < mUsedSize.mX; j++) {
            auto c = line[j];
            output_apply_style(c.style());
            outStream << c.character();
        }
        outStream << std::endl;
    }
    output_end();
}

void TextCanvas::clear() {
    mUsedSize = Size();
    mCursorPos = Point();
}

void TextCanvas::move_cursor(const Point &vector) {
    mCursorPos += vector;
    _layout_cursor();
}

TextCanvas::TextCanvas(TextCanvas *parent) {
    mParent = parent;
}

void TextCanvas::_check_size(const Size &size) {
    if (size.width() <= 0 || size.height() <= 0) {
        std::stringstream ss;
        ss << "Invalid size " + size.to_string();
        throw cpe::Exception(ss.str());
    }
}

void TextCanvas::_print_symbol(char c) {
    if (mEof)
        return;

    auto &sym = mMatrix[mCursorPos.mY][mCursorPos.mX];
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
    while (mCursorPos.mY >= mMatrix.size())
        mMatrix.push_back(TextLine(static_cast<TextLine::size_type>(mSize.mX)));
}

}