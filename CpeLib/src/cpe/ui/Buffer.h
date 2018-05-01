#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include "cpe/core/Color.h"
#include "cpe/core/Point.h"
#include "cpe/core/terminal.h"
#include "WriterFormat.h"

namespace cpe {

/**
 * Буффер специальных символов для последующего вывода в стандартный поток вывода
 */
class Buffer {
public:

    Buffer();

    ~Buffer();

    bool colorMode() const;

    void colorMode(bool settingBackground);

    bool color(cpe::Color &color) const;

    void color(const cpe::Color &color);

    void clearColor();

    bool maxWidth(int &width) const;

    void maxWidth(int width);

    void clearMaxWidth();

    bool maxHeight(int &height) const;

    void maxHeight(int height);

    void clearMaxHeight();

    const WriterFormat &format() const;

    void format(const WriterFormat &format);

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

    // Символы буфера
    std::vector<_Symbol> mSymbols;
    // Режим применения цвета
    bool mColorSetBg = false;
    // Цвет текста
    _Color mFore;
    // Увет фона
    _Color mBack;
    // Ширина
    _Maximum mWidth;
    // Высота
    _Maximum mHeight;
    // Форматер вывода
    WriterFormat mFormat;

    // Раскрывает все подбуферы, указанные в данном буфере
    Point _simplify(std::vector<_StyledChar> &chars,
                    Point outerPos,
                    const _Maximum &outerMaxWidth,
                    const _Maximum &outerMaxHeight) const;

    // Пробует добавить строку учитывая заданные максимальные ширину и высоту, если заданы
    inline bool
    _tryAddLine(Point &local,
                const Point &outer,
                const _Maximum &maxWidth,
                const _Maximum &maxHeight,
                std::vector<_StyledChar> &chars) const;
};

}




