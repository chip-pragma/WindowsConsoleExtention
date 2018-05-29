#include "Buffer.h"
#include "cpe/core/Exception.h"

#include <cstddef>
#include <sstream>
#include <cmath>

namespace cpe {

namespace {

inline bool __charIsOneOf(const std::string &chars, char src) {
    return (chars.find(src) != std::string::npos);
}

// Проверяет значение точки как значения размера
inline void __point_as_size(const Point &size);

// Новая строка
inline void __newLine(Point &cursorPos);


// Максимальная позиция курсора в рамках холста
inline Point __clampPoint(const Point &point, const Point &size);

// Позиция курсора в рамках холста
inline bool __isPointInBounds(const Point &point, const Point &size);


inline void __point_as_size(const Point &size) {
    if (size.calcLocation() != Point::PL_SECTOR_I) {
        std::stringstream ss;
        ss << "Invalid getWidth " + size.toString();
        throw cpe::Exception(ss.str());
    }
}

inline void __newLine(Point &cursorPos) {
    cursorPos.getX() = 0;
    cursorPos += Point(0, 1);
}

Point __clampPoint(const Point &point, const Point &size) {
    Point clamped(std::min(std::max(point.getX(),
                                    int32_t(0)), size.getX() - 1),
                  std::min(std::max(point.getY(),
                                    int32_t(0)), size.getY() - 1));
    return clamped;
}

inline bool __isPointInBounds(const Point &point, const Point &size) {
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
    return (__clampPoint(mMaxCurPos, mSize) + 1);
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

    if (!__isPointInBounds(begin, mSize) ||
        !__isPointInBounds(end, mSize + 1))
        throw Exception("Invalid begin position and/or getWidth");

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
    for (size_t i = 0; i < text.getLength(); ++i) {
        auto ch = text[i];
        if (__charIsOneOf("\n\r", ch.getChar())) {
            __newLine(mCursorPos);
        } else if (ch.getChar() == '\t') {
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
    __newLine(mCursorPos);
}

void Buffer::draw(const Buffer &sub, bool useActualSize) {
    // Исключение рекурсии
    if (&sub == this)
        return;

    const Point srcCurPos = mCursorPos;
    Point thisMaxSize = mSize - srcCurPos;
    Point subUsedSize = sub.mSize;
    if (useActualSize)
        subUsedSize = __clampPoint(sub.mMaxCurPos, sub.mSize) + 1;
    const Point size(std::min(thisMaxSize.getX(), subUsedSize.getX()),
                     std::min(thisMaxSize.getY(), subUsedSize.getY()));

    for (int i = 0; i < size.getY(); i++) {
        for (int j = 0; j < size.getX(); j++) {
            Point coord(j + srcCurPos.getX(), i + srcCurPos.getY());
            if (__isPointInBounds(coord, mSize)) {
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

    if (__charIsOneOf("\n\r\t", schar.getChar()))
        schar.setChar(' ');

    for (int i = 0, n = std::abs(count); i < n; i++) {
        __pointWithMaxCrd();
        __printChar(schar);
        mCursorPos += direct;
    }
}

void Buffer::outputTo(std::ostream &outStream) const {
    auto maxSize = (__clampPoint(mMaxCurPos, mSize) + 1);
    OutputHelper outHelp;

    outHelp.beginColorize(outStream);
    for (int i = 0; i < maxSize.getY(); i++) {
        auto line = mBuffer[i];
        for (int j = 0; j < maxSize.getX(); j++) {
            auto c = line[j];
            outHelp.applyColor(c.getColor());
            outStream << c.getChar();
        }
        outStream << std::endl;
    }
    outHelp.endColorize();
}

void Buffer::clear() {
    for (int i = 0; i < mSize.getY(); i++)
        for (int j = 0; j < mSize.getX(); j++)
            mBuffer[i][j] = StyledChar();
    mMaxCurPos = mCursorPos = Point();
}

const StyledChar &Buffer::at(const Point &pos) const {
    if (!__isPointInBounds(pos, mSize))
        throw Exception("Out of range");
    return mBuffer[pos.getY()][pos.getX()];
}

StyledChar &Buffer::at(const Point &pos) {
    if (!__isPointInBounds(pos, mSize))
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
    if (__isPointInBounds(mCursorPos, mSize)) {
        mBuffer[mCursorPos.getY()][mCursorPos.getX()] = schar;
    }
}

void Buffer::__printText(const StyledChar &schar) {
    if (mCursorPos.getX() >= mSize.getX())
        __newLine(mCursorPos);
    __pointWithMaxCrd();
    __printChar(schar);
    mCursorPos.getX()++;
}

void Buffer::__pointWithMaxCrd() {
    mMaxCurPos.getX() = std::max(mMaxCurPos.getX(), mCursorPos.getX());
    mMaxCurPos.getY() = std::max(mMaxCurPos.getY(), mCursorPos.getY());

    auto current = this;
    auto next = mOwner;
    while (next) {
        Point &ownerMaxPos = next->mMaxCurPos;
        Point thisMaxPos = __clampPoint(current->mMaxCurPos, current->mSize) + current->mBeginPosFromOwner;
        ownerMaxPos.getX() = std::max(ownerMaxPos.getX(), thisMaxPos.getX());
        ownerMaxPos.getY() = std::max(ownerMaxPos.getY(), thisMaxPos.getY());
        current = next;
        next = next->mOwner;
    }
}

}