#include "Buffer.h"

namespace cpe {

Buffer::Buffer() : mMaxWidth(0),
                   mMaxHeight(0),
                   mFormat(WriterFormat()) {}

Buffer::Buffer(const WriterFormat &format) : mMaxWidth(0),
                                             mMaxHeight(0),
                                             mFormat(format) {}

Buffer::Buffer(int16_t mw, int16_t mh) : mMaxWidth(mw),
                                         mMaxHeight(mh),
                                         mFormat(WriterFormat()) {
    if (mMaxWidth <= 0)
        mMaxWidth = cpe::term::getBufferSize().x;
}

Buffer::Buffer(const WriterFormat &format,
               int16_t mw, int16_t mh) : mMaxWidth(mw),
                                         mMaxHeight(mh),
                                         mFormat(format) {}

Buffer::~Buffer() {
    clear();
}

void Buffer::resize(int16_t mw, int16_t mh) {
    if (mMaxWidth <= 0)
        mMaxWidth = cpe::term::getBufferSize().x;
}

bool Buffer::getForeColor(cpe::Color &color) const {
    if (mForeUsing)
        color = mFore;
    return mForeUsing;
}

void Buffer::setForeColor(const cpe::Color &fore) {
    mFore = fore;
    mForeUsing = true;
}

bool Buffer::getBackColor(cpe::Color &color) const {
    if (mBackUsing)
        color = mBack;
    return mBackUsing;
}

void Buffer::setBackColor(const cpe::Color &back) {
    mBack = back;
    mBackUsing = true;
}

void Buffer::unsetForeColor() {
    mForeUsing = false;
}

void Buffer::unsetBackColor() {
    mBackUsing = false;
}

void Buffer::write(const std::string &str) {
    if (mMaxHeight > 0 &&
        mMatrix.size() == mMaxHeight &&
        mCurCol == mMaxWidth)
        return;

    nBufSym *last = nullptr;
    if (mMatrix.empty())
        last = _matrixAddLine();
    else
        last = mMatrix.back();

    for (char c : str) {
        if (!last)
            break;

        if (c == '\n' ||
            c == '\r') {
            last = _matrixAddLine();
        } else if (c == '\t') {
            auto tl = mFormat.getTabLength();
            auto sc = ((mCurCol / tl + 1) * tl) - mCurCol;
            if (mCurCol + sc >= mMaxWidth)
                last = _matrixAddLine();
            else
                for (int i = 0; i < sc; i++)
                    _matrixSetBufChar(last, mCurCol++, ' ');
        } else {
            _matrixSetBufChar(last, mCurCol++, c);
        }

        if (mCurCol == mMaxWidth)
            last = _matrixAddLine();
    }
}

void Buffer::flush() {
    bool useAutoFlush = std::cout.flags() & std::ios_base::unitbuf;
    if (useAutoFlush)
        std::cout << std::nounitbuf;

    const auto srcForeCol = cpe::term::getForeColor();
    const auto srcBackCol = cpe::term::getBackColor();

    for (auto line : mMatrix) {
        for (int i = 0; i < mMaxWidth; i++) {
            const auto &bs = line[i];

            if (bs.mForeUsing)
                cpe::term::setForeColor(bs.mFore);
            else
                cpe::term::setForeColor(srcForeCol);
            if (bs.mBackUsing)
                cpe::term::setBackColor(bs.mBack);
            else
                cpe::term::setBackColor(srcBackCol);

            std::cout << bs.mChar;
        }
        std::cout << "\n";
    }
    clear();

    cpe::term::setForeColor(srcForeCol);
    cpe::term::setBackColor(srcBackCol);

    std::cout.flush();
    if (useAutoFlush)
        std::cout << std::unitbuf;
}

void Buffer::back(uint64_t count) {
    if (count <= 0 || mMatrix.empty())
        return;

    if (count > mMatrix.size())
        mMatrix.clear();
    else {
        auto ei = mMatrix.begin();
        mMatrix.erase(ei - count, ei);
    }
}

void Buffer::clear() {
    for (auto line : mMatrix)
        delete[] line;
    mMatrix.clear();
}

Buffer &Buffer::operator<<(const std::string &str) {
    write(str);
    return *this;
}

Buffer::nBufSym *Buffer::_matrixAddLine() {
    nBufSym *newLine = nullptr;
    if (mMaxHeight <= 0
        || mMatrix.size() < mMaxHeight) {
        newLine = new nBufSym[mMaxWidth];
        mMatrix.push_back(newLine);
        mCurCol = 0;
    } else {
        auto uf = mFormat.getUnfinished();
        auto min = uf.size() < mMaxWidth ? uf.size() : mMaxWidth;
        auto last = mMatrix.back();

        mCurCol = static_cast<int16_t>(mMaxWidth - min);
        for (size_t i = 0; i < min; i++) {
            _matrixSetBufChar(last, mCurCol++, uf[i]);
        }
    }
    return newLine;
}

void Buffer::_matrixSetBufChar(nBufSym *line, int16_t column, char c) {
    auto &bs = line[column];
    bs.mChar = c;
    if (mForeUsing) {
        bs.mForeUsing = true;
        bs.mFore = mFore;
    }
    if (mBackUsing) {
        bs.mBackUsing = true;
        bs.mBack = mBack;
    }
}

}