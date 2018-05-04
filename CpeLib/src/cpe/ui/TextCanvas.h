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

    TextCanvas &print(const TextCanvas &buffer);

    void outputTo(std::basic_ostream<char> &outStream) const;

    void clear();

    const Point &moveCursor(const Point &vector);

    TextCanvas &operator<<(const std::string &str);

    TextCanvas &operator<<(const TextCanvas &buf);

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

    Point mActualSize;
    Point mMaxSize = Point(DEFAULT_MAX_WIDTH, DEFAULT_MAX_HEIGHT);
    TextFormat mFormat;

};

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const TextCanvas &buffer);

}




