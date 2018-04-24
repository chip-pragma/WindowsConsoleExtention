#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "cpe/core/Color.h"
#include "cpe/core/Point.h"
#include "cpe/core/Terminal.h"
#include "WriterFormat.h"

namespace cpe {

class Buffer {
public:

    Buffer();

    ~Buffer();

    bool isColorSetBg() const;

    void setColorSetBg(bool colorSetMode);

    bool getColor(cpe::Color &color) const;

    void setColor(const cpe::Color &color);

    void unsetColor();

    bool getWidth(int &width) const;

    void setWidth(int width);

    void unsetWidth();

    bool getHeight(int &height) const;

    void setHeight(int height);

    void unsetHeight();

    const WriterFormat &getFormat() const;

    void setFormat(const WriterFormat &format);

    Buffer &pushBack(const std::string &str);

    Buffer &pushBack(const Buffer &buffer);

    void flush();

    void popBack(uint64_t count);

    void clear();

    Buffer &operator<<(const std::string &str);

    Buffer &operator<<(Buffer &(*manip)(Buffer &));

    Buffer &operator<<(const Buffer &buf);

private:
    struct _Color {
        Color mColor;
        bool mUsing = false;
    };

    struct _StyledChar {
        _StyledChar() {

        }

        _StyledChar(const _Color &fore,
                    const _Color &back,
                    char aChar) : mFore(fore),
                                  mBack(back),
                                  mChar(aChar) {}

        _Color mFore;
        _Color mBack;
        char mChar = ' ';
    };

    struct _Symbol {
        enum : int {
            UNDEFINED,
            BUFFER_POINTER,
            STYLED_CHAR
        };

        _Symbol() {

        }

        explicit _Symbol(const Buffer *buffer) : mBuffer(buffer),
                                                 mType(BUFFER_POINTER) {}

        explicit _Symbol(const _StyledChar &styledChar) : mSChar(styledChar),
                                                          mType(STYLED_CHAR) {}

        int mType = UNDEFINED;
        union {
            const Buffer *mBuffer = nullptr;
            _StyledChar mSChar;
        };
    };

    struct _Maximum {
        int mValue = 0;
        bool mUsing = false;

        _Maximum() {

        }

        explicit _Maximum(int val) : mValue(val) {
            mUsing = true;
        }
    };

    std::vector<_Symbol> mSymbols;
    bool mColorSetBg = false;
    _Color mFore;
    _Color mBack;
    _Maximum mWidth;
    _Maximum mHeight;
    WriterFormat mFormat;

    Point _simplify(std::vector<_StyledChar> &chars, Point outerPos, const _Maximum &outerMaxWidth,
                    const _Maximum &outerMaxHeight) const;

    inline bool
    _tryAddLine(Point &local, const Point &outer, const _Maximum &maxWidth, const _Maximum &maxHeight,
                std::vector<_StyledChar> &chars) const;
};

}




