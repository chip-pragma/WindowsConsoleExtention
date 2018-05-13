#include "TextCanvas.h"
#include "cpe/core/Exception.h"

#include <cstddef>
#include <sstream>
#include <cmath>

namespace cpe {

namespace {


// Проверяет значение точки как значения размера
inline void __point_as_size(const Point &size);

// "Печатает" символ в допустимой области холста
inline void
__print_char(char chr, StyledChar **matrix, const Point &cursorPos, const TextCharStyle &style, const Point &size);

// Печатает текстовый символ (с пропуском строки и т.п.)
inline void __print_text(char c, StyledChar **matrix, Point &cursorPos, const TextCharStyle &style, const Point &size,
                         Point &maxCursorPos);

// Новая строка
inline void __new_line(Point &cursorPos);

// Расчет максимальной позиции курсора
inline Point __point_with_max_crd(const Point &point1, const Point &point2);

// Максимальная позиция курсора в рамках холста
inline Point __clamp_point(const Point &point, const Point &size);

// Позиция курсора в рамках холста
inline bool __is_point_in_bounds(const Point &point, const Point &size);


inline void __point_as_size(const Point &size) {
    if (size.dimension() != Point::DIM_SECTOR_I) {
        std::stringstream ss;
        ss << "Invalid size " + size.to_string();
        throw cpe::Exception(ss.str());
    }
}

inline void
__print_char(char chr, StyledChar **matrix, const Point &cursorPos, const TextCharStyle &style, const Point &size) {
    if (__is_point_in_bounds(cursorPos, size)) {
        auto &sym = matrix[cursorPos.y_crd()][cursorPos.x_crd()];
        sym.character(chr);
        sym.style(style);
    }
}

inline void __print_text(char c, StyledChar **matrix, Point &cursorPos, const TextCharStyle &style, const Point &size,
                         Point &maxCursorPos) {
    if (cursorPos.x_crd() >= size.x_crd())
        __new_line(cursorPos);
    maxCursorPos = __point_with_max_crd(cursorPos, maxCursorPos);
    __print_char(c, matrix, cursorPos, style, size);
    cursorPos += Point(1, 0);
}

inline void __new_line(Point &cursorPos) {
    cursorPos.x_crd(0);
    cursorPos += Point(0, 1);
}

inline Point __point_with_max_crd(const Point &point1, const Point &point2) {
    Point max;
    max.x_crd(std::max(point2.x_crd(), point1.x_crd()));
    max.y_crd(std::max(point2.y_crd(), point1.y_crd()));
    return max;
}

Point __clamp_point(const Point &point, const Point &size) {
    Point clamped(std::clamp(point.x_crd(),
                             int32_t(0), size.x_crd() - 1),
                  std::clamp(point.y_crd(),
                             int32_t(0), size.y_crd() - 1));
    return clamped;
}

inline bool __is_point_in_bounds(const Point &point, const Point &size) {
    return (point.x_crd() >= 0 && point.x_crd() < size.x_crd() &&
            point.y_crd() >= 0 && point.y_crd() < size.y_crd());
}

}

TextCanvas::TextCanvas(const Point &size) {
    __point_as_size(size);
    mSize = size;

    mMatrix = new StyledChar *[size.y_crd()];
    for (int i = 0; i < size.y_crd(); i++)
        mMatrix[i] = new StyledChar[size.x_crd()];
}

TextCanvas::~TextCanvas() {
    if (!mOwner) {
        for (int i = 0; i < mSize.y_crd(); i++)
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

const Point &TextCanvas::size() const {
    return mSize;
}

Point TextCanvas::calc_used_size() const {
    return (mMaxCurPos + 1);
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

TextCanvas TextCanvas::extract(const Point &begin, const Point &size) {
    auto end = begin + size;

    if (!__is_point_in_bounds(begin, mSize) ||
        !__is_point_in_bounds(end, mSize))
        throw Exception("Invalid begin position and/or size");

    TextCanvas result(this, size);

    result.mMatrix = new StyledChar *[size.y_crd()];
    for (int i = 0; i < size.y_crd(); i++) {
        result.mMatrix[i] = &mMatrix[begin.y_crd() + i][begin.x_crd()];
    }

    return result;
}

void TextCanvas::draw(const std::string &str) {
    for (char c : str) {
        if (c == '\n' || c == '\r') {
            __new_line(mCursorPos);
        } else if (c == '\t') {
            auto tl = format().tab_length();
            auto sc = tl - mCursorPos.x_crd() % tl;
            for (int16_t i = 0; i < sc; i++)
                __print_text(' ', mMatrix, mCursorPos, mCursorStyle, mSize, mMaxCurPos);
        } else {
            __print_text(c, mMatrix, mCursorPos, mCursorStyle, mSize, mMaxCurPos);
        }
    }
}

void TextCanvas::draw_line(const std::string &str) {
    draw(str + "\n");
}

void TextCanvas::draw(const TextCanvas &sub, bool useActualSize) {
    // Исключение рекурсии
    if (&sub == this)
        return;

    const Point srcCurPos = mCursorPos;
    Point thisMaxSize = mSize - srcCurPos;
    Point subUsedSize = sub.mSize;
    if (useActualSize)
        subUsedSize = __clamp_point(sub.mMaxCurPos, sub.mSize) + 1;
    const Point size(std::min(thisMaxSize.x_crd(), subUsedSize.x_crd()),
                     std::min(thisMaxSize.y_crd(), subUsedSize.y_crd()));

    for (int i = 0; i < size.y_crd(); i++) {
        for (int j = 0; j < size.x_crd(); j++) {
            Point coord(j + srcCurPos.x_crd(), i + srcCurPos.y_crd());
            if (__is_point_in_bounds(coord, mSize)) {
                mMatrix[coord.y_crd()][coord.x_crd()]
                        = sub.mMatrix[i][j];
            }
            cursor_position(Point(srcCurPos.x_crd(), srcCurPos.y_crd() + i));
            mMaxCurPos = __point_with_max_crd(mCursorPos, mMaxCurPos);
        }
    }
}

void TextCanvas::draw(char character, int32_t count, bool vertical) {
    Point direct(1, 0);
    if (vertical)
        direct = {0, 1};
    if (std::signbit(count))
        direct *= -1;

    if (character == '\n' || character == '\r' || character == '\t')
        character = ' ';

    for (int i = 0, n = std::abs(count); i < n; i++) {
        mMaxCurPos = __point_with_max_crd(mCursorPos, mMaxCurPos);
        __print_char(character, mMatrix, mCursorPos, mCursorStyle, mSize);
        mCursorPos += direct;
    }
}

void TextCanvas::output_to(std::ostream &outStream) const {
    auto maxSize = (__clamp_point(mMaxCurPos, mSize) + 1);

    output_begin(outStream);
    for (int i = 0; i < maxSize.y_crd(); i++) {
        auto line = mMatrix[i];
        for (int j = 0; j < maxSize.x_crd(); j++) {
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
    if (!__is_point_in_bounds(pos, mSize))
        throw Exception("Out of range");
    return mMatrix[pos.y_crd()][pos.x_crd()];
}

StyledChar &TextCanvas::at(const Point &pos) {
    if (!__is_point_in_bounds(pos, mSize))
        throw Exception("Out of range");
    return mMatrix[pos.y_crd()][pos.x_crd()];
}

StyledChar &TextCanvas::operator[](const Point &pos) {
    return at(pos);
}

TextCanvas::TextCanvas(TextCanvas *parent, const Point &size) : mOwner(parent),
                                                                mSize(size) {

}


}