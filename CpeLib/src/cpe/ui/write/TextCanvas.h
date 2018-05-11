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
#include "WriteHelper.h"
#include "TextFormat.h"
#include "StyledChar.h"
#include "TextLine.h"

namespace cpe {

class TextCanvas : public WriteHelper {
public:
    enum CursorMoving : int32_t {
        CURSOR_MOVING_STANDART = 0,
        CURSOR_MOVING_VERTICAL = 1,
        CURSOR_MOVING_NO_WRAP = 2,
        CURSOR_MOVING_REVERSE = 4
    };

    explicit TextCanvas(const Point &maxSize);

    ~TextCanvas();

    const Point &cursor_position() const;

    void cursor_position(const Point &pos);

    const TextCharStyle &cursor_style() const;

    TextCharStyle &cursor_style();

    void cursor_style(const TextCharStyle &cursorStyle);

    int32_t cursor_moving() const;

    void cursor_moving(CursorMoving cursorMoving);

    const TextFormat &format() const;

    TextFormat &format();

    void format(const TextFormat &wf);

    const Point &max_size() const;

    const Point &actual_size() const;

    void draw(const std::string &str);

    void draw(const TextCanvas &canvas, bool useActualSize);

    void draw_line(const std::string &str = "");

    void output_to(std::ostream &outStream) const;

    void clear();

    void move_cursor(const Point &vector);

private:
    TextCharStyle mCursorStyle;
    int32_t mCursorMoving = CURSOR_MOVING_STANDART;
    std::vector<TextLine> mLines;
    bool mEof = false;
    TextFormat mFormat;
    Point mCursorPos;
    Point mActualSize;
    Point mMaxSize;
    // x - print char, y - wrap line
    Point mIteration;
    struct {
        int16_t *curPos1;
        int16_t *curPos2;
        int16_t *actSize1;
        int16_t *actSize2;
        int16_t *maxSize1;
        int16_t *maxSize2;
        int16_t *iteration1;
        int16_t *iteration2;
    } mPtr;

    inline void _print_symbol(char c);

    inline void _wrap();

    inline void _layout_cursor();

    inline void _add_lines();
};

}




