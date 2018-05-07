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
#include "TextFormat.h"
#include "TextChar.h"
#include "TextLine.h"

namespace cpe {

class TextCanvas {
public:
    TextCanvas(const Point &maxSize);

    ~TextCanvas();

    Nullable <Color> & foreground() const;

    void foreground(const Nullable<Color> &fore);

    Nullable <Color> & background() const;

    void background(const Nullable<Color> &back);

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
    Nullable<Color> mFore;
    Nullable<Color> mBack;
    Point mCursor;

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




