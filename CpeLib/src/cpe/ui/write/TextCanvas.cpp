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

    mMatrix = new StyledChar *[size.height()];
    for (int i = 0; i < size.height(); i++)
        mMatrix[i] = new StyledChar[size.width()];
}

TextCanvas::~TextCanvas() {
    if (!mOwner) {
        for (int i = 0; i < mSize.height(); i++)
            delete[] mMatrix[i];
        delete[] mMatrix;
    }
}

const Point &TextCanvas::cursor_position() const {
    return mCursorPos;
}

void TextCanvas::cursor_position(const Point &pos) {
    mCursorPos = pos;
}

void TextCanvas::move_cursor(const Point &vector) {
    mCursorPos += vector;
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

const Size &TextCanvas::size() const {
    return mSize;
}

Size TextCanvas::calc_used_size() const {
    return (mMaxCurPos + 1).to_size();
}

bool TextCanvas::have_owner() const {
    return static_cast<bool>(mOwner);
}

const TextCanvas &TextCanvas::owner() const {
    if (!mOwner)
        throw Exception("TextCanvas does not have parent");
    return *mOwner;
}

TextCanvas &TextCanvas::owner() {
    if (!mOwner)
        throw Exception("TextCanvas does not have parent");
    return *mOwner;
}

TextCanvas TextCanvas::extract(const Point &begin, const Size &size) {
    // TODO получить вложенный холст


}

void TextCanvas::draw(const std::string &str) {
    for (char c : str) {
        if (c == '\n' || c == '\r') {
            _new_line();
        } else if (c == '\t') {
            auto tl = format().getTabLength();
            auto sc = tl - mCursorPos.coord_x() % tl;
            for (int16_t i = 0; i < sc; i++)
                _print_char(' ');
        } else {
            _print_char(c);
        }
    }
}

void TextCanvas::draw(const TextCanvas &canvas, bool useActualSize) {
    // Исключение рекурсии
    if (&canvas == this)
        return;

    // TODO рисование холста в золст проверить

    /*const Point srcCurPos = mCursorPos;
    Size maxSize = mSize - srcCurPos.to_size();
    Size usingSize = canvas.mSize;
    if (useActualSize)
        usingSize = canvas.mMaxCurPos;
    const Size size(std::min(maxSize.width(), usingSize.width()),
                     std::min(maxSize.height(), usingSize.height()));

    for (int i = 0; i < size.height(); i++) {
        for (int j = 0; j < size.width(); j++) {
            mMatrix[i + srcCurPos.coord_y()][j + srcCurPos.coord_x()]
                    = canvas.mMatrix[i][j];
            cursor_position(Point(srcCurPos.coord_x(), srcCurPos.coord_y() + i));
        }
    }*/
}

void TextCanvas::draw(char character, uint32_t count, const CursorMoving &moving) {

}

void TextCanvas::output_to(std::ostream &outStream) const {
    auto maxCurPosToSize = (mMaxCurPos + 1).to_size();
    Size maxSize(
            std::clamp(maxCurPosToSize.width(),
                       uint32_t(0), mSize.width()),
            std::clamp(maxCurPosToSize.height(),
                       uint32_t(0), mSize.height()));

    output_begin(outStream);
    for (int i = 0; i < maxSize.height(); i++) {
        auto line = mMatrix[i];
        for (int j = 0; j < maxSize.width(); j++) {
            auto c = line[j];
            output_apply_style(c.style());
            outStream << c.character();
        }
        outStream << std::endl;
    }
    output_end();
}

void TextCanvas::clear() {
    mMaxCurPos = mCursorPos = Point();
}

TextCanvas::TextCanvas(TextCanvas *parent) {
    mOwner = parent;
}

inline void TextCanvas::_check_size(const Size &size) {
    if (size.width() <= 0 || size.height() <= 0) {
        std::stringstream ss;
        ss << "Invalid size " + size.to_string();
        throw cpe::Exception(ss.str());
    }
}

inline void TextCanvas::_print_char(char c) {
    if (mCursorPos.coord_x() >= mSize.width())
        _new_line();

    if (_check_size_limits()) {
        auto &sym = mMatrix[mCursorPos.coord_y()][mCursorPos.coord_x()];
        sym.character(c);
        sym.style(mCursorStyle);
    }

    mCursorPos += Point(1, 0);
    mMaxCurPos.coord_x(std::max(mMaxCurPos.coord_x(), mCursorPos.coord_x()));
    mMaxCurPos.coord_y(std::max(mMaxCurPos.coord_y(), mCursorPos.coord_y()));
}

inline void TextCanvas::_new_line() {
    mCursorPos += Point(0, 1);
    mCursorPos.coord_x(0);

}

inline bool TextCanvas::_check_size_limits() const {
    return (mCursorPos.coord_x() >= 0 && mCursorPos.coord_x() < mSize.width() &&
            mCursorPos.coord_y() >= 0 && mCursorPos.coord_y() < mSize.height());
}

}