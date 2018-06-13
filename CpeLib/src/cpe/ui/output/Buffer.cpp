#include "Buffer.h"
#include "cpe/core/Exception.h"

#include <cstddef>
#include <sstream>
#include <cmath>

namespace cpe {

namespace {

inline bool _charContains(const std::string &chars, char src) {
    return (chars.find(src) != std::string::npos);
}

inline void _pointSectorI(const Point &size);

inline void _newLine(Point &cursorPos);

inline Point _clampPointToBounds(const Point &point, const Point &size);

// Позиция курсора в рамках холста
inline bool _isPointInBounds(const Point &point, const Point &size);


inline void _pointSectorI(const Point &size) {
    if (size.getLocation() != Point::PL_SECTOR_I) {
        std::stringstream ss;
        ss << "Invalid getWidth " + size.toString();
        throw cpe::Exception(ss.str());
    }
}

inline void _newLine(Point &cursorPos) {
    cursorPos.getXRef() = 0;
    cursorPos += Point(0, 1);
}

Point _clampPointToBounds(const Point &point, const Point &size) {
    Point clamped(std::min(std::max(point.getX(),
                                    int32_t(0)), size.getX() - 1),
                  std::min(std::max(point.getY(),
                                    int32_t(0)), size.getY() - 1));
    return clamped;
}

inline bool _isPointInBounds(const Point &point, const Point &size) {
    return (point.getX() >= 0 && point.getX() < size.getX() &&
        point.getY() >= 0 && point.getY() < size.getY());
}

}

Buffer::Buffer(const Point &size) {
    _pointSectorI(size);
    mSize = size;

    mBuffer = new StyledChar *[size.getY()];
    // FEATURE создание новых строк по мере необходимости, а не сразу.
    for (int i = 0; i < size.getY(); i++)
        mBuffer[i] = new StyledChar[size.getX()];
}

Buffer::~Buffer() {
    if (!mOwner) {
        for (int i = 0; i < mSize.getYRef(); i++)
            delete[] mBuffer[i];
        delete[] mBuffer;
    }
}

const Point &Buffer::getCursorPos() const {
    return mCursorPos;
}

Point &Buffer::getCursorPosRef() {
    return mCursorPos;
}

const Point &Buffer::getSize() const {
    return mSize;
}

Point Buffer::getUsedSize() const {
    return (_clampPointToBounds(mMaxCurPos, mSize) + 1);
}

const uint8_t &Buffer::getTabLength() const {
    return mTabLength;
}

uint8_t &Buffer::getTabLengthRef() {
    return mTabLength;
}

const std::string &Buffer::getUnfinished() const {
    return mUnfinished;
}

std::string &Buffer::getUnfinishedRef() {
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

    if (!_isPointInBounds(begin, mSize) ||
        !_isPointInBounds(end, mSize + 1))
        throw Exception("Invalid begin position and/or getWidth");

    Buffer result(this, begin, size);

    result.mBuffer = new StyledChar *[size.getYRef()];
    for (int i = 0; i < size.getYRef(); i++) {
        auto row = &mBuffer[begin.getYRef() + i][begin.getXRef()];
        if (clean)
            for (int j = 0; j < size.getXRef(); j++)
                row[j] = StyledChar();
        result.mBuffer[i] = row;
    }

    return result;
}

void Buffer::draw(const StyledText &text, bool softWrap) {
    // FEATURE Добавить как нибудь "мягкие" разрывы строк
    for (size_t i = 0; i < text.getLength(); ++i) {
        auto ch = text[i];
        if (_charContains("\n\r", ch.getChar())) {
            _newLine(mCursorPos);
        } else if (ch.getChar() == '\t') {
            auto sc = mTabLength - mCursorPos.getXRef() % mTabLength;
            for (int32_t j = 0; j < sc; j++)
                printTextChar(ch);
        } else {
            printTextChar(ch);
        }
    }
}

void Buffer::drawLine(const StyledText &str, bool softWrap) {
    draw(str, false);
    _newLine(mCursorPos);
}

void Buffer::draw(const Buffer &sub, bool useActualSize) {
    // Исключение рекурсии
    if (&sub == this)
        return;

    const Point srcCurPos = mCursorPos;
    Point thisMaxSize = mSize - srcCurPos;
    Point subUsedSize = sub.mSize;
    if (useActualSize)
        subUsedSize = _clampPointToBounds(sub.mMaxCurPos, sub.mSize) + 1;
    const Point size(std::min(thisMaxSize.getXRef(), subUsedSize.getXRef()),
                     std::min(thisMaxSize.getYRef(), subUsedSize.getYRef()));

    for (int i = 0; i < size.getY(); i++) {
        for (int j = 0; j < size.getX(); j++) {
            Point coord(j + srcCurPos.getX(), i + srcCurPos.getY());
            if (_isPointInBounds(coord, mSize)) {
                mBuffer[coord.getYRef()][coord.getXRef()]
                    = sub.mBuffer[i][j];
            }
            getPointWithMaxCrd();
            getCursorPosRef() = Point(srcCurPos.getX(), srcCurPos.getY() + i);
        }
    }
}

void Buffer::draw(StyledChar schar, int32_t count, bool vertical) {
    Point direct(1, 0);
    if (vertical)
        direct = {0, 1};
    if (std::signbit(count))
        direct *= -1;

    if (_charContains("\n\r\t", schar.getChar()))
        schar.setChar(' ');

    for (int i = 0, n = std::abs(count); i < n; i++) {
        getPointWithMaxCrd();
        printChar(schar);
        mCursorPos += direct;
    }
}

void Buffer::outputTo(std::ostream &outStream) const {
    auto maxSize = (_clampPointToBounds(mMaxCurPos, mSize) + 1);
    OutputHelper outHelp;

    outHelp.beginColorize(outStream);
    for (int i = 0; i < maxSize.getYRef(); i++) {
        auto line = mBuffer[i];
        for (int j = 0; j < maxSize.getXRef(); j++) {
            auto c = line[j];
            outHelp.applyColor(c.getColorRef());
            outStream << c.getChar();
        }
        outStream << std::endl;
    }
    outHelp.endColorize();
}

void Buffer::clear() {
    for (int i = 0; i < mSize.getYRef(); i++)
        for (int j = 0; j < mSize.getXRef(); j++)
            mBuffer[i][j] = StyledChar();
    mMaxCurPos = mCursorPos = Point();
}

const StyledChar &Buffer::at(const Point &pos) const {
    if (!_isPointInBounds(pos, mSize))
        throw Exception("Out of range");
    return mBuffer[pos.getY()][pos.getX()];
}

StyledChar &Buffer::at(const Point &pos) {
    if (!_isPointInBounds(pos, mSize))
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

void Buffer::printChar(const StyledChar &schar) {
    if (_isPointInBounds(mCursorPos, mSize)) {
        mBuffer[mCursorPos.getYRef()][mCursorPos.getXRef()] = schar;
    }
}

void Buffer::printTextChar(const StyledChar &schar) {
    if (mCursorPos.getXRef() >= mSize.getXRef())
        _newLine(mCursorPos);
    getPointWithMaxCrd();
    printChar(schar);
    mCursorPos.getXRef()++;
}

void Buffer::getPointWithMaxCrd() {
    mMaxCurPos.getXRef() = std::max(mMaxCurPos.getXRef(), mCursorPos.getXRef());
    mMaxCurPos.getYRef() = std::max(mMaxCurPos.getYRef(), mCursorPos.getYRef());

    auto current = this;
    auto next = mOwner;
    while (next) {
        Point &ownerMaxPos = next->mMaxCurPos;
        Point thisMaxPos = _clampPointToBounds(current->mMaxCurPos, current->mSize) + current->mBeginPosFromOwner;
        ownerMaxPos.getXRef() = std::max(ownerMaxPos.getXRef(), thisMaxPos.getXRef());
        ownerMaxPos.getYRef() = std::max(ownerMaxPos.getYRef(), thisMaxPos.getYRef());
        current = next;
        next = next->mOwner;
    }
}

}