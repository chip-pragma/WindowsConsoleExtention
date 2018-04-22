#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "cpe/core/Color.h"
#include "cpe/core/Terminal.h"
#include "cpe/core/WriterFormat.h"

namespace cpe {

class Buffer {
public:

    Buffer();

    explicit Buffer(const WriterFormat &format);

    Buffer(int16_t mw, int16_t mh);

    Buffer(const WriterFormat &format, int16_t maxWidth, int16_t maxHeight);

    ~Buffer();

    void resize(int16_t mw, int16_t mh);

    bool getForeColor(cpe::Color &color) const;

    void setForeColor(const cpe::Color &fore);

    bool getBackColor(cpe::Color &color) const;

    void setBackColor(const cpe::Color &back);

    void unsetForeColor();

    void unsetBackColor();

    void write(const std::string &str);

    void flush();

    void back(uint64_t count);

    void clear();

    Buffer &operator<<(const std::string &str);

private:
    class nBufSym {
    public:
        cpe::Color mFore;
        cpe::Color mBack;
        bool mForeUsing = false;
        bool mBackUsing = false;
        char mChar = ' ';
    };

    std::vector<nBufSym *> mMatrix;
    int16_t mCurCol = 0;
    cpe::Color mFore;
    cpe::Color mBack;
    bool mForeUsing = false;
    bool mBackUsing = false;
    int16_t mMaxWidth = 0;
    int16_t mMaxHeight = 0;
    cpe::WriterFormat mFormat;

    Buffer::nBufSym *_matrixAddLine();

    void _matrixSetBufChar(nBufSym *line, int16_t column, char c);
};

}




