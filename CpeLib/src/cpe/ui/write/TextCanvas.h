#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include "cpe/core/draw/Color.h"
#include "cpe/core/draw/Point.h"
#include "cpe/core/draw/Point.h"
#include "cpe/core/terminal.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "WriteHelper.h"
#include "TextFormat.h"
#include "StyledChar.h"

namespace cpe {

class TextCanvas : public WriteHelper {
public:

    explicit TextCanvas(const Point &size);

    ~TextCanvas();

    const Point &cursor_position() const;

    void cursor_position(const Point &pos);

    void move_cursor(const Point &vector);

    const TextCharStyle &cursor_style() const;

    TextCharStyle &cursor_style();

    void cursor_style(const TextCharStyle &cursorStyle);

    const TextFormat &format() const;

    TextFormat &format();

    void format(const TextFormat &wf);

    const Point & size() const;

    Point calc_used_size() const;

    bool have_owner() const;

    const TextCanvas& owner() const;

    TextCanvas& owner();

    TextCanvas extract(const Point &begin, const Point &size);

    void draw(const std::string &str);

    void draw_line(const std::string &str = "");

    void draw(const TextCanvas &sub, bool useActualSize);

    void draw(char character, int32_t count = 1, bool vertical = true);

    void output_to(std::ostream &outStream) const;

    void clear();

    const StyledChar &at(const Point &pos) const;

    StyledChar &at(const Point &pos);

    StyledChar &operator[](const Point &pos);

private:
    Point mCursorPos;
    TextCharStyle mCursorStyle;
    StyledChar** mMatrix;
    TextCanvas* mOwner = nullptr;
    TextFormat mFormat;
    Point mSize;
    Point mMaxCurPos;

    explicit TextCanvas(TextCanvas *parent, const Point &size);
};

}




