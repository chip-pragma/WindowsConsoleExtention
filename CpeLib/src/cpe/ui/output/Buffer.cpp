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
        ss << "Invalid width " + size.toString();
        throw cpe::Exception(ss.str());
    }
}

inline void __new_line(Point &cursorPos) {
    cursorPos.getX() = 0;
    cursorPos += Point(0, 1);
}

Point __clamp_point(const Point &point, const Point &size) {
    Point clamped(std::min(std::max(point.getX(),
                                    int32_t(0)), size.getX() - 1),
                  std::min(std::max(point.getY(),
                                    int32_t(0)), size.getY() - 1));
    return clamped;
}

inline bool __is_point_in_bounds(const Point &point, const Point &size) {
    return (point.getX() >= 0 && point.getX() < size.getX() &&
        point.getY() >= 0 && point.getY() < size.getY());
}

}

Buffer::Buffer(const Point &size) {
    __point_as_size(size);
    mSize = size;

    mBuffer = new StyledChar *[size.getY()];
    for (int i = 0; i < size.getY(); i++)
        mBuffer[i] = new StyledChar[size.getX()];
}

Buffer::~Buffer() {
    if (!mOwner) {
        for (int i = 0; i < mSize.getY(); i++)
            delete[] mBuffer[i];
        delete[] mBuffer;
    }
}

const Point &Buffer::getCursorPos() const {
    return mCursorPos;
}

Point &Buffer::getCursorPos() {
    return mCursorPos;
}

const Point &Buffer::getSize() const {
    return mSize;
}

Point Buffer::getUsedSize() const {
    return (__clamp_point(mMaxCurPos, mSize) + 1);
}

const uint8_t &Buffer::getTabLength() const {
    return mTabLength;
}

uint8_t &Buffer::getTabLength() {
    return mTabLength;
}

const std::string &Buffer::unfinished() const {
    return mUnfinished;
}

std::string &Buffer::unfinished() {
    return mUnfinished;
}

bool Buffer::hasOwner() const {
    return static_cast<bool>(mOwner);
}

const Buffer &Buffer::getOwner() const {
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

    result.mBuffer = new StyledChar *[size.getY()];
    for (int i = 0; i < size.getY(); i++) {
        auto row = &mBuffer[begin.getY() + i][begin.getX()];
        if (clean)
            for (int j = 0; j < size.getX(); j++)
                row[j] = StyledChar();
        result.mBuffer[i] = row;
    }

    return result;
}

void Buffer::draw(const StyledText &text, bool softWrap) {
    // FEATURE Добавить как нибудь "мягкие" разрывы строк
    for (size_t i = 0; i < text.length(); ++i) {
        auto ch = text[i];
        if (__char_is_one_of("\n\r", ch.character())) {
            __new_line(mCursorPos);
        } else if (ch.character() == '\t') {
            auto sc = mTabLength - mCursorPos.getX() % mTabLength;
            for (int32_t j = 0; j < sc; j++)
                __printText(ch);
        } else {
            __printText(ch);
        }
    }
}

void Buffer::drawLine(const StyledText &str, bool softWrap) {
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
    const Point size(std::min(thisMaxSize.getX(), subUsedSize.getX()),
                     std::min(thisMaxSize.getY(), subUsedSize.getY()));

    for (int i = 0; i < size.getY(); i++) {
        for (int j = 0; j < size.getX(); j++) {
            Point coord(j + srcCurPos.getX(), i + srcCurPos.getY());
            if (__is_point_in_bounds(coord, mSize)) {
                mBuffer[coord.getY()][coord.getX()]
                    = sub.mBuffer[i][j];
            }
            __pointWithMaxCrd();
            getCursorPos() = Point(srcCurPos.getX(), srcCurPos.getY() + i);
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
        __pointWithMaxCrd();
        __printChar(schar);
        mCursorPos += direct;
    }
}

void Buffer::outputTo(std::ostream &outStream) const {
    auto maxSize = (__clamp_point(mMaxCurPos, mSize) + 1);
    OutputHelper outHelp;

    outHelp.begin_colorized(outStream);
    for (int i = 0; i < maxSize.getY(); i++) {
        auto line = mBuffer[i];
        for (int j = 0; j < maxSize.getX(); j++) {
            auto c = line[j];
            outHelp.apply_color(c.color());
            outStream << c.character();
        }
        outStream << std::endl;
    }
    outHelp.end_colorized();
}

void Buffer::clear() {
    for (int i = 0; i < mSize.getY(); i++)
        for (int j = 0; j < mSize.getX(); j++)
            mBuffer[i][j] = StyledChar();
    mMaxCurPos = mCursorPos = Point();
}

const StyledChar &Buffer::at(const Point &pos) const {
    if (!__is_point_in_bounds(pos, mSize))
        throw Exception("Out of range");
    return mBuffer[pos.getY()][pos.getX()];
}

StyledChar &Buffer::at(const Point &pos) {
    if (!__is_point_in_bounds(pos, mSize))
        throw Exception("Out of range");
    return mBuffer[pos.getY()][pos.getX()];
}

StyledChar &Buffer::operator[](const Point &pos) {
    return at(pos);
}

Buffer::Buffer(Buffer *parent,
               const Point &beginPos,
               const Point &size) : mOwner(parent),
                                    mSize(size),
                                    mBeginPosFromOwner(beginPos) { }

void Buffer::__printChar(const StyledChar &schar) {
    if (__is_point_in_bounds(mCursorPos, mSize)) {
        mBuffer[mCursorPos.getY()][mCursorPos.getX()] = schar;
    }
}

void Buffer::__printText(const StyledChar &schar) {
    if (mCursorPos.getX() >= mSize.getX())
        __new_line(mCursorPos);
    __pointWithMaxCrd();
    __printChar(schar);
    mCursorPos += Point(1, 0);
}

void Buffer::__pointWithMaxCrd() {
    mMaxCurPos.getX() = std::max(mMaxCurPos.getX(), mCursorPos.getX());
    mMaxCurPos.getY() = std::max(mMaxCurPos.getY(), mCursorPos.getY());

    if (mOwner) {
        Point &ownerMaxPos = mOwner->mMaxCurPos;
        Point thisMaxPos = __clamp_point(mMaxCurPos, mSize) + mBeginPosFromOwner;
        ownerMaxPos.getX() = std::max(ownerMaxPos.getX(), thisMaxPos.getX());
        ownerMaxPos.getY() = std::max(ownerMaxPos.getY(), thisMaxPos.getY());
    }
}

}