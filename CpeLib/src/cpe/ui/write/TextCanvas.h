#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include "cpe/core/Color.h"
#include "cpe/core/Point.h"
#include "cpe/core/terminal.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "cpe/ui/WriteHelper.h"
#include "TextFormat.h"
#include "TextChar.h"
#include "TextLine.h"

namespace cpe {

class TextCanvas : public WriteHelper {
public:
    explicit TextCanvas(const Point &maxSize);

    ~TextCanvas();

    Point &cursor_position();

    void cursor_position(const Point &pos);

    TextCharStyle &cursor_style();

    void cursor_style(const TextCharStyle &cursorStyle);

    void format(const TextFormat &wf);

    const TextFormat &format();

    const Point &max_size() const;

    const Point &actual_size() const;

    TextCanvas &draw(const std::string &str);

    TextCanvas &draw(const TextCanvas &canvas);

    void output_to(std::ostream &outStream) const;

    void clear();

    void move_cursor(const Point &vector);

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

    inline void _print_symbol(char c);

    inline void _new_line();

    inline void _layout_cursor();

    inline void _add_lines();
};

std::ostream &operator<<(std::ostream &stream, const TextCanvas &buffer);

}




