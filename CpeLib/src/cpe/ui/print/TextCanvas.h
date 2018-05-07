#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include "cpe/core/Color.h"
#include "cpe/core/Point.h"
#include "cpe/core/terminal.h"
#include "cpe/tool/property/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "TextFormat.h"
#include "TextChar.h"
#include "TextLine.h"

namespace cpe {

class TextCanvas {
public:
    TextCanvas(const Point &maxSize);

    ~TextCanvas();

    Point &cursorPosition();

    void cursorPosition(const Point &pos);

    TextCharStyle &cursorStyle();

    void cursorStyle(const TextCharStyle &cursorStyle);

    void setFormat(const TextFormat &wf);

    const TextFormat &getFormat();

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
    TextCharStyle mCursorStyle;
    Point mCursorPos;

    std::vector<TextLine> mLines;
    bool mEof = false;

    Point mActualSize;
    Point mMaxSize;
    TextFormat mFormat;

    inline void _printSymbol(char c);

    inline void _newLine();

    inline void _layoutCursor();

    inline void _addLines();
};

std::ostream &operator<<(std::ostream &stream, const TextCanvas &buffer);

}




