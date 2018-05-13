#include "TextCanvas.h"
#include "cpe/core/Exception.h"

#include <cstddef>
#include <sstream>
#include <cmath>

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
    __check_size(size);
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
    auto end = begin + size.to_point();

    if (!__check_size_limits(begin) ||
        !__check_size_limits(end))
        throw Exception("Invalid begin position and/or size");

    TextCanvas result(this, size);

    result.mMatrix = new StyledChar*[size.height()];
    for (int i = 0; i < size.height(); i++) {
        result.mMatrix[i] = &mMatrix[begin.coord_y() + i][begin.coord_x()];
    }

    return result;
}

void TextCanvas::draw(const std::string &str) {
    for (char c : str) {
        if (c == '\n' || c == '\r') {
            __new_line();
        } else if (c == '\t') {
            auto tl = format().tab_length();
            auto sc = tl - mCursorPos.coord_x() % tl;
            for (int16_t i = 0; i < sc; i++)
                __print_text_char(' ');
        } else {
            __print_text_char(c);
        }
    }
}

void TextCanvas::draw(const TextCanvas &sub, bool useActualSize) {
    // Исключение рекурсии
    if (&sub == this)
        return;

    const Point srcCurPos = mCursorPos;
    Point thisMaxSize = mSize.to_point() - srcCurPos;
    Point subUsedSize = sub.mSize.to_point();
    if (useActualSize)
        subUsedSize = sub.__get_clamped_max_cur_pos() + 1;
    const Point size(std::min(thisMaxSize.coord_x(), subUsedSize.coord_x()),
                     std::min(thisMaxSize.coord_y(), subUsedSize.coord_y()));

    for (int i = 0; i < size.coord_y(); i++) {
        for (int j = 0; j < size.coord_x(); j++) {
            Point coord(j + srcCurPos.coord_x(), i + srcCurPos.coord_y());
            if (__check_size_limits(coord)) {
                mMatrix[coord.coord_y()][coord.coord_x()]
                        = sub.mMatrix[i][j];
            }
            cursor_position(Point(srcCurPos.coord_x(), srcCurPos.coord_y() + i));
            __max_cursor_position();
        }
    }
}

void TextCanvas::draw(char character, int32_t count, bool vertical) {
    Point direct(1, 0);
    if (vertical)
        direct = {0, 1};
    if (std::signbit(count))
        direct *= -1;

    for (int i = 0, n = std::abs(count); i < n; i++) {
        __max_cursor_position();
        __print_char(character);
        mCursorPos += direct;
    }
}

void TextCanvas::output_to(std::ostream &outStream) const {
    auto maxSize = (__get_clamped_max_cur_pos() + 1).to_size();

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

const StyledChar &TextCanvas::at(const Point &pos) const {
    if (!__check_size_limits(pos))
        throw Exception("Out of range");
    return mMatrix[pos.coord_y()][pos.coord_x()];
}

StyledChar &TextCanvas::at(const Point &pos) {
    if (!__check_size_limits(pos))
        throw Exception("Out of range");
    return mMatrix[pos.coord_y()][pos.coord_x()];
}

StyledChar &TextCanvas::operator[](const Point &pos) {
    return at(pos);
}

TextCanvas::TextCanvas(TextCanvas *parent, const Size &size) : mOwner(parent),
                                                               mSize(size) {

}

inline void TextCanvas::__check_size(const Size &size) {
    if (size.width() <= 0 || size.height() <= 0) {
        std::stringstream ss;
        ss << "Invalid size " + size.to_string();
        throw cpe::Exception(ss.str());
    }
}

inline void TextCanvas::__print_char(char c) {
    if (__check_size_limits(mCursorPos)) {
        auto &sym = mMatrix[mCursorPos.coord_y()][mCursorPos.coord_x()];
        sym.character(c);
        sym.style(mCursorStyle);
    }
}

inline void TextCanvas::__print_text_char(char c) {
    if (mCursorPos.coord_x() >= mSize.to_point().coord_x())
        __new_line();
    __max_cursor_position();
    __print_char(c);
    mCursorPos += Point(1, 0);
}

inline void TextCanvas::__new_line() {
    mCursorPos.coord_x(0);
    mCursorPos += Point(0, 1);
}

inline void TextCanvas::__max_cursor_position() {
    mMaxCurPos.coord_x(std::max(mMaxCurPos.coord_x(), mCursorPos.coord_x()));
    mMaxCurPos.coord_y(std::max(mMaxCurPos.coord_y(), mCursorPos.coord_y()));
}

Point TextCanvas::__get_clamped_max_cur_pos() const {
    Point clamped(
            std::clamp(mMaxCurPos.coord_x(),
                       int32_t(0), mSize.to_point().coord_x() - 1),
            std::clamp(mMaxCurPos.coord_y(),
                       int32_t(0), mSize.to_point().coord_y() - 1));
    return clamped;
}

inline bool TextCanvas::__check_size_limits(const Point &point) const {
    return (point.coord_x() >= 0 && point.coord_x() < mSize.to_point().coord_x() &&
            point.coord_y() >= 0 && point.coord_y() < mSize.to_point().coord_y());
}

}