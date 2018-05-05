#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>

#include "cpe/core/Color.h"
#include "cpe/core/Point.h"
#include "cpe/core/terminal.h"

#include "TextFormat.h"

namespace cpe {

class TextCanvas {
public:
    TextCanvas(uint16_t maxWidth, uint16_t maxHeight);

    ~TextCanvas();

    //region pen

    void setPen(const Color &color);

    void getPen(std::nullptr_t);

    const Color &unsetPen(const Color &defColor) const;

    //endregion

    //region brush

    void setBrush(const Color &color);

    void getBrush(std::nullptr_t);

    const Color &unsetBrush(const Color &defColor) const;

    //endregion

    //region cursor

    void setCursor(const Point &pos);

    const Point &getCursor();

    //endregion

    //region format

    void setFormat(const TextFormat &wf);

    const TextFormat &getFormat();

    //endregion

    const Point &getMaxSize() const;

    const Point &getActualSize() const;

    TextCanvas &print(const std::string &str);

    TextCanvas &print(const TextCanvas &canvas);

    void outputTo(std::ostream &outStream) const;

    void clear();

    void moveCursor(const Point &vector);

    TextCanvas &operator<<(const std::string &str);

    TextCanvas &operator<<(const TextCanvas &canvas);

private:
    struct {
        Color *fore = nullptr;
        Color *back = nullptr;
        Point position;
    } mPrintCursor;

    struct _StyledChar {
        _StyledChar() {}

        _StyledChar(Color *fore,
                    Color *back,
                    char aChar) : fore(fore),
                                  back(back),
                                  character(aChar) {}

        Color *fore = nullptr;
        Color *back = nullptr;
        char character = ' ';
    };

    std::vector<_StyledChar *> mLines;
    bool mEof = false;

    Point mActualSize;
    Point mMaxSize;
    TextFormat mFormat;

    inline void _printSymbol(char c);

    inline void _newLine();

    inline void _layoutCursor();

    inline void _addLines();

    int16_t _max(const int16_t &v1, const int16_t &v2) const;

    int16_t _min(const int16_t &v1, const int16_t &v2) const;
};

std::ostream &operator<<(std::ostream &stream, const TextCanvas &buffer);

}




