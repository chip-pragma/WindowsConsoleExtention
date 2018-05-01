#include "Buffer.h"

namespace cpe {

Buffer::Buffer() : mFormat(WriterFormat()) {}

Buffer::~Buffer() {
    clear();
}

bool Buffer::colorMode() const {
    return mColorSetBg;
}

void Buffer::colorMode(bool settingBackground) {
    mColorSetBg = settingBackground;
}

bool Buffer::color(cpe::Color &color) const {
    auto col = &mFore;
    if (mColorSetBg)
        col = &mBack;

    if (col->mUsing)
        color = col->mColor;
    return col->mUsing;
}

void Buffer::color(const cpe::Color &color) {
    auto col = &mFore;
    if (mColorSetBg)
        col = &mBack;

    col->mUsing = true;
    col->mColor = color;
}

void Buffer::clearColor() {
    auto col = &mFore;
    if (mColorSetBg)
        col = &mBack;
    col->mUsing = false;
}

bool Buffer::maxWidth(int &width) const {
    if (mWidth.mUsing)
        width = mWidth.mValue;
    return mWidth.mUsing;
}

void Buffer::maxWidth(int width) {
    mWidth.mValue = width;
    mWidth.mUsing = (width > 0);
}

void Buffer::clearMaxWidth() {
    mWidth.mUsing = false;
}

bool Buffer::maxHeight(int &height) const {
    if (mHeight.mUsing)
        height = mHeight.mValue;
    return mHeight.mUsing;
}

void Buffer::maxHeight(int height) {
    mHeight.mValue = height;
    mHeight.mUsing = (height > 0);
}

void Buffer::clearMaxHeight() {
    mHeight.mUsing = false;
}

const WriterFormat &Buffer::format() const {
    return mFormat;
}

void Buffer::format(const WriterFormat &format) {
    mFormat = format;
}

Buffer & Buffer::pushBack(const std::string &str) {
    for (char c : str) {
        mSymbols.push_back(_Symbol(_StyledChar(mFore, mBack, c)));
    }
}

Buffer & Buffer::pushBack(const Buffer &buffer) {
    mSymbols.push_back(_Symbol(&buffer));
}

void Buffer::flush() {
    bool useAutoFlush = std::cout.flags() & std::ios_base::unitbuf;
    if (useAutoFlush)
        std::cout << std::nounitbuf;

    const auto srcForeCol = term::foreground();
    const auto srcBackCol = term::background();

    std::vector<_StyledChar> resultChars;
    auto bsize = term::outputBufferSize();
    _Maximum bw(bsize.x);
    _Maximum bh(bsize.y);
    _simplify(resultChars, Point(), bw, bh);

    for (auto c : resultChars) {
        if (c.mFore.mUsing) term::foreground(c.mFore.mColor);
        else term::foreground(srcForeCol);
        if (c.mBack.mUsing) term::background(c.mBack.mColor);
        else term::background(srcBackCol);
        std::cout << c.mChar;
    }
    std::cout.flush();
    clear();

    term::foreground(srcForeCol);
    term::background(srcBackCol);

    if (useAutoFlush)
        std::cout << std::unitbuf;
}

void Buffer::popBack(uint64_t count) {
    if (count >= mSymbols.size())
        clear();
    else {
        auto ei = mSymbols.end();
        mSymbols.erase(ei - count, ei);
    }
}

void Buffer::clear() {
    mSymbols.clear();
}

Buffer &Buffer::operator<<(const std::string &str) {
    return pushBack(str);
}

Buffer &Buffer::operator<<(Buffer &(*manip)(Buffer &)) {
    manip(*this);
    return *this;
}

Buffer & Buffer::operator<<(const Buffer &buf) {
    // Исключение рекурсии
    if (&buf != this)
        pushBack(buf);
    return *this;
}

Point Buffer::_simplify(std::vector<_StyledChar> &chars, Point outerPos,
                        const _Maximum &outerMaxWidth, const _Maximum &outerMaxHeight) const {

    _Maximum width = mWidth;
    if (outerMaxWidth.mUsing) {
        if (!width.mUsing || width.mValue > outerMaxWidth.mValue)
            width = outerMaxWidth;
    }
    _Maximum height = mHeight;
    if (outerMaxHeight.mUsing) {
        if (!height.mUsing || height.mValue > outerMaxHeight.mValue)
            height = outerMaxHeight;
    }

    Point localPosition;

    bool breakForFlag = false;
    for (auto sym : mSymbols) {
        switch (sym.mType) {
            case _Symbol::BUFFER_POINTER:
                localPosition = sym.mBuffer->_simplify(
                        chars, outerPos + localPosition,
                        _Maximum(width.mValue - localPosition.x),
                        _Maximum(height.mValue - localPosition.y));
                break;
            case _Symbol::STYLED_CHAR:
                // NEW LINE
                if (sym.mSChar.mChar == '\n'
                    || sym.mSChar.mChar == '\r') {
                    breakForFlag = !_tryAddLine(localPosition, outerPos, width, height, chars);
                }
                    // TAB
                else if (sym.mSChar.mChar == '\t') {
                    auto tl = mFormat.getTabLength();
                    auto sc = (tl - localPosition.x % tl);
                    if (width.mUsing && sc + localPosition.x >= width.mValue)
                        breakForFlag = !_tryAddLine(localPosition, outerPos, width, height, chars);
                    else {
                        chars.insert(chars.end(), static_cast<uint64_t>(sc), _StyledChar());
                        localPosition.x += sc;
                    }
                }
                    // CHAR
                else {
                    chars.push_back(sym.mSChar);
                    localPosition.x++;
                    if (width.mUsing && localPosition.x == width.mValue) {
                        breakForFlag = !_tryAddLine(localPosition, outerPos, width, height, chars);
                    }
                }
                break;
            default:
                break;
        }

        if (breakForFlag)
            break;
    }

    return localPosition + outerPos;
}

inline bool Buffer::_tryAddLine(Point &local, const Point &outer,
                                const _Maximum &maxWidth, const _Maximum &maxHeight,
                                std::vector<_StyledChar> &chars) const {
    auto limit = (maxHeight.mUsing && local.y + 1 >= maxHeight.mValue);
    if (limit) {
        auto uf = mFormat.getUnfinished();
        auto sc = local.x;
        auto ei = chars.end();

        if (maxWidth.mUsing) {
            sc = (short) maxWidth.mValue - local.x - (short) uf.size();
            if (sc < 0) {
                sc = -sc < (short) maxWidth.mValue ? -sc : (short) maxWidth.mValue;
                chars.erase(ei - sc, ei);
            }
        }

        for (int i = 0; i < sc; i++) {
            chars.push_back(_StyledChar(mFore, mBack, uf[i]));
            local.x++;
        }
    } else {
        chars.push_back(_StyledChar(mFore, mBack, '\n'));
        chars.insert(chars.end(), static_cast<uint64_t>(outer.x), _StyledChar());
        local.y++;
        local.x = 0;
    }
    return !limit;
}

}