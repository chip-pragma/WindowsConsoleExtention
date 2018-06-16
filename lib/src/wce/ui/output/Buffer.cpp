#include "Buffer.h"
#include "wce/core/Exception.h"

#include <cstddef>
#include <sstream>
#include <cmath>

namespace wce {

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
        throw wce::Exception(ss.str());
    }
}

inline void _newLine(Point &cursorPos) {
    cursorPos.x = 0;
    cursorPos += Point(0, 1);
}

Point _clampPointToBounds(const Point &point, const Point &size) {
    Point clamped(std::min(std::max(point.x,
                                    int32_t(0)), size.x - 1),
                  std::min(std::max(point.y,
                                    int32_t(0)), size.y - 1));
    return clamped;
}

inline bool _isPointInBounds(const Point &point, const Point &size) {
    return (point.x >= 0 && point.x < size.x &&
            point.y >= 0 && point.y < size.y);
}

}

Buffer::Buffer(const Point &size) {
    _pointSectorI(size);
    m_size = size;

    m_buffer = new StyledChar *[size.y];
    // FEATURE создание новых строк по мере необходимости, а не сразу.
    for (int i = 0; i < size.y; i++)
        m_buffer[i] = new StyledChar[size.x];
}

Buffer::~Buffer() {
    if (!m_owner) {
        for (int i = 0; i < m_size.y; i++)
            delete[] m_buffer[i];
        delete[] m_buffer;
    }
}

const Point &Buffer::getSize() const {
    return m_size;
}

Point Buffer::getUsedSize() const {
    return (_clampPointToBounds(m_maxCurPos, m_size) + 1);
}

bool Buffer::hasOwner() const {
    return static_cast<bool>(m_owner);
}

const Buffer &Buffer::getOwner() const {
    if (!m_owner)
        throw Exception("Buffer does not have parent");
    return *m_owner;
}

Buffer Buffer::extract(Point begin, Point size, bool clean) {
    auto end = begin + size;

    if (!_isPointInBounds(begin, m_size) ||
        !_isPointInBounds(end, m_size + 1))
        throw Exception("Invalid begin position and/or getWidth");

    Buffer result(this, begin, size);

    result.m_buffer = new StyledChar *[size.y];
    for (int i = 0; i < size.y; i++) {
        auto row = &m_buffer[begin.y + i][begin.x];
        if (clean)
            for (int j = 0; j < size.x; j++)
                row[j] = StyledChar();
        result.m_buffer[i] = row;
    }

    return result;
}

void Buffer::draw(const StyledText &text, bool softWrap) {
    // FEATURE Добавить как нибудь "мягкие" разрывы строк
    for (size_t i = 0; i < text.getLength(); ++i) {
        auto ch = text[i];
        if (_charContains("\n\r", ch.character)) {
            _newLine(cursorPosition);
        } else if (ch.character == '\t') {
            auto sc = tabLength - cursorPosition.x % tabLength;
            for (int32_t j = 0; j < sc; j++)
                printTextChar(ch);
        } else {
            printTextChar(ch);
        }
    }
}

void Buffer::drawLine(const StyledText &str, bool softWrap) {
    draw(str, false);
    _newLine(cursorPosition);
}

void Buffer::draw(const Buffer &sub, bool useActualSize) {
    // Исключение рекурсии
    if (&sub == this)
        return;

    const Point srcCurPos = cursorPosition;
    Point thisMaxSize = m_size - srcCurPos;
    Point subUsedSize = sub.m_size;
    if (useActualSize)
        subUsedSize = _clampPointToBounds(sub.m_maxCurPos, sub.m_size) + 1;
    const Point size(std::min(thisMaxSize.x, subUsedSize.x),
                     std::min(thisMaxSize.y, subUsedSize.y));

    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            Point coord(j + srcCurPos.x, i + srcCurPos.y);
            if (_isPointInBounds(coord, m_size)) {
                m_buffer[coord.y][coord.x]
                    = sub.m_buffer[i][j];
            }
            getPointWithMaxCrd();
            cursorPosition = Point(srcCurPos.x, srcCurPos.y + i);
        }
    }
}

void Buffer::draw(StyledChar schar, int32_t count, bool vertical) {
    Point direct(1, 0);
    if (vertical)
        direct = {0, 1};
    if (std::signbit(count))
        direct *= -1;

    if (_charContains("\n\r\t", schar.character))
        schar.character = ' ';

    for (int i = 0, n = std::abs(count); i < n; i++) {
        getPointWithMaxCrd();
        printChar(schar);
        cursorPosition += direct;
    }
}

void Buffer::outputTo(std::ostream &outStream) const {
    auto maxSize = (_clampPointToBounds(m_maxCurPos, m_size) + 1);
    OutputHelper outHelp;

    outHelp.beginColorize(outStream);
    for (int i = 0; i < maxSize.y; i++) {
        auto line = m_buffer[i];
        for (int j = 0; j < maxSize.x; j++) {
            auto c = line[j];
            outHelp.applyColor(c.color);
            outStream << c.character;
        }
        outStream << std::endl;
    }
    outHelp.endColorize();
}

void Buffer::clear() {
    for (int i = 0; i < m_size.y; i++)
        for (int j = 0; j < m_size.x; j++)
            m_buffer[i][j] = StyledChar();
    m_maxCurPos = cursorPosition = Point();
}

const StyledChar &Buffer::at(const Point &pos) const {
    if (!_isPointInBounds(pos, m_size))
        throw Exception("Out of range");
    return m_buffer[pos.y][pos.x];
}

StyledChar &Buffer::at(const Point &pos) {
    if (!_isPointInBounds(pos, m_size))
        throw Exception("Out of range");
    return m_buffer[pos.y][pos.x];
}

StyledChar &Buffer::operator[](const Point &pos) {
    return at(pos);
}

Buffer::Buffer(Buffer *parent,
               const Point &beginPos,
               const Point &size) : m_owner(parent),
                                    m_size(size),
                                    m_beginPosFromOwner(beginPos) { }

void Buffer::printChar(const StyledChar &schar) {
    if (_isPointInBounds(cursorPosition, m_size)) {
        m_buffer[cursorPosition.y][cursorPosition.x] = schar;
    }
}

void Buffer::printTextChar(const StyledChar &schar) {
    if (cursorPosition.x >= m_size.x)
        _newLine(cursorPosition);
    getPointWithMaxCrd();
    printChar(schar);
    cursorPosition.x++;
}

void Buffer::getPointWithMaxCrd() {
    m_maxCurPos.x = std::max(m_maxCurPos.x, cursorPosition.x);
    m_maxCurPos.y = std::max(m_maxCurPos.y, cursorPosition.y);

    auto current = this;
    auto next = m_owner;
    while (next) {
        Point &ownerMaxPos = next->m_maxCurPos;
        Point thisMaxPos = _clampPointToBounds(current->m_maxCurPos, current->m_size) + current->m_beginPosFromOwner;
        ownerMaxPos.x = std::max(ownerMaxPos.x, thisMaxPos.x);
        ownerMaxPos.y = std::max(ownerMaxPos.y, thisMaxPos.y);
        current = next;
        next = next->m_owner;
    }
}

}