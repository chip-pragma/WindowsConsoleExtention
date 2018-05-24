#include "Buffer.h"
#include "cpe/core/Exception.h"

#include <cstddef>
#include <sstream>
#include <cmath>

namespace cpe {

namespace {

inline bool __char_is_one_of(const std::string &chars, char src) {
    return (chars.find(src) != std::string::npos);
}

// Проверяет значение точки как значения размера
inline void __point_as_size(const Point &size);

// Новая строка
inline void __new_line(Point &cursorPos);


// Максимальная позиция курсора в рамках холста
inline Point __clamp_point(const Point &point, const Point &size);

// Позиция курсора в рамках холста
inline bool __is_point_in_bounds(const Point &point, const Point &size);


inline void __point_as_size(const Point &size) {
    if (size.dimension() != Point::DIM_SECTOR_I) {
        std::stringstream ss;
        ss << "Invalid width " + size.to_string();
        throw cpe::Exception(ss.str());
    }
}

inline void __new_line(Point &cursorPos) {
    cursorPos.x_crd() = 0;
    cursorPos += Point(0, 1);
}

Point __clamp_point(const Point &point, const Point &size) {
    Point clamped(std::min(std::max(point.x_crd(),
                                    int32_t(0)), size.x_crd() - 1),
                  std::min(std::max(point.y_crd(),
                                    int32_t(0)), size.y_crd() - 1));
    return clamped;
}

inline bool __is_point_in_bounds(const Point &point, const Point &size) {
    return (point.x_crd() >= 0 && point.x_crd() < size.x_crd() &&
            point.y_crd() >= 0 && point.y_crd() < size.y_crd());
}

}

Buffer::Buffer(const Point &size) {
    __point_as_size(size);
    mSize = size;

    mBuffer = new StyledChar *[size.y_crd()];
    for (int i = 0; i < size.y_crd(); i++)
        mBuffer[i] = new StyledChar[size.x_crd()];
}

Buffer::~Buffer() {
    if (!mOwner) {
        for (int i = 0; i < mSize.y_crd(); i++)
            delete[] mBuffer[i];
        delete[] mBuffer;
    }
}

const Point &Buffer::cursor_position() const {
    return mCursorPos;
}

Point &Buffer::cursor_position() {
    return mCursorPos;
}

const Point &Buffer::get_size() const {
    return mSize;
}

Point Buffer::get_used_size() const {
    return (__clamp_point(mMaxCurPos, mSize) + 1);
}

bool Buffer::has_owner() const {
    return static_cast<bool>(mOwner);
}

const Buffer &Buffer::get_owner() const {
    if (!mOwner)
        throw Exception("Buffer does not have parent");
    return *mOwner;
}

Buffer Buffer::extract(Point begin, Point size, bool clean) {
    auto end = begin + size;

    if (!__is_point_in_bounds(begin, mSize) ||
        !__is_point_in_bounds(end, mSize + 1))
        throw Exception("Invalid begin position and/or width");

    Buffer result(this, begin, size);

    result.mBuffer = new StyledChar *[size.y_crd()];
    for (int i = 0; i < size.y_crd(); i++) {
        auto row = &mBuffer[begin.y_crd() + i][begin.x_crd()];
        if (clean)
            for (int j = 0; j < size.x_crd(); j++)
                row[j] = StyledChar();
        result.mBuffer[i] = row;
    }

    return result;
}

void Buffer::draw(const StyledText &text, bool softWrap) {
    // TODO Добавить как нибудь "мягкие" разрывы строк
    for (auto it = text.cbegin(); it != text.cend(); ++it) {
        if (__char_is_one_of("\n\r", it->character())) {
            __new_line(mCursorPos);
        } else if (it->character() == '\t') {
            auto tl = text.tab_length();
            auto sc = tl - mCursorPos.x_crd() % tl;
            for (int32_t i = 0; i < sc; i++)
                __print_text(*it);
        } else {
            __print_text(*it);
        }
    }
}

void Buffer::draw_line(const StyledText &str, bool softWrap) {
    draw(str, false);
    __new_line(mCursorPos);
}

void Buffer::draw(const Buffer &sub, bool useActualSize) {
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
                mBuffer[coord.y_crd()][coord.x_crd()]
                        = sub.mBuffer[i][j];
            }
            __point_with_max_crd();
            cursor_position() = Point(srcCurPos.x_crd(), srcCurPos.y_crd() + i);
        }
    }
}

void Buffer::draw(StyledChar schar, int32_t count, bool vertical) {
    Point direct(1, 0);
    if (vertical)
        direct = {0, 1};
    if (std::signbit(count))
        direct *= -1;

    if (__char_is_one_of("\n\r\t", schar.character()))
        schar.character(' ');

    for (int i = 0, n = std::abs(count); i < n; i++) {
        __point_with_max_crd();
        __print_char(schar);
        mCursorPos += direct;
    }
}

void Buffer::output_to(std::ostream &outStream) const {
    auto maxSize = (__clamp_point(mMaxCurPos, mSize) + 1);
    OutputHelper outHelp;

    outHelp.begin_colorized(outStream);
    for (int i = 0; i < maxSize.y_crd(); i++) {
        auto line = mBuffer[i];
        for (int j = 0; j < maxSize.x_crd(); j++) {
            auto c = line[j];
            outHelp.apply_color(c.color());
            outStream << c.character();
        }
        outStream << std::endl;
    }
    outHelp.end_colorized();
}

void Buffer::clear() {
    for (int i = 0; i < mSize.y_crd(); i++)
        for (int j = 0; j < mSize.x_crd(); j++)
            mBuffer[i][j] = StyledChar();
    mMaxCurPos = mCursorPos = Point();
}

const StyledChar &Buffer::at(const Point &pos) const {
    if (!__is_point_in_bounds(pos, mSize))
        throw Exception("Out of range");
    return mBuffer[pos.y_crd()][pos.x_crd()];
}

StyledChar &Buffer::at(const Point &pos) {
    if (!__is_point_in_bounds(pos, mSize))
        throw Exception("Out of range");
    return mBuffer[pos.y_crd()][pos.x_crd()];
}

StyledChar &Buffer::operator[](const Point &pos) {
    return at(pos);
}

Buffer::Buffer(Buffer *parent, const Point &beginPos, const Point &size) : mOwner(parent),
                                                                           mSize(size),
                                                                           mBeginPosFromOwner(beginPos) {

}

void Buffer::__print_char(const StyledChar &schar) {
    if (__is_point_in_bounds(mCursorPos, mSize)) {
        mBuffer[mCursorPos.y_crd()][mCursorPos.x_crd()] = schar;
    }
}

void Buffer::__print_text(const StyledChar &schar) {
    if (mCursorPos.x_crd() >= mSize.x_crd())
        __new_line(mCursorPos);
    __point_with_max_crd();
    __print_char(schar);
    mCursorPos += Point(1, 0);
}

void Buffer::__point_with_max_crd() {
    mMaxCurPos.x_crd() = std::max(mMaxCurPos.x_crd(), mCursorPos.x_crd());
    mMaxCurPos.y_crd() = std::max(mMaxCurPos.y_crd(), mCursorPos.y_crd());

    if (mOwner) {
        Point &ownerMaxPos = mOwner->mMaxCurPos;
        Point thisMaxPos = __clamp_point(mMaxCurPos, mSize) + mBeginPosFromOwner;
        ownerMaxPos.x_crd() = std::max(ownerMaxPos.x_crd(), thisMaxPos.x_crd());
        ownerMaxPos.y_crd() = std::max(ownerMaxPos.y_crd(), thisMaxPos.y_crd());
    }
}

}