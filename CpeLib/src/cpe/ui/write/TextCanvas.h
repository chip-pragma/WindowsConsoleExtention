#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include "cpe/core/draw/Color.h"
#include "cpe/core/draw/Point.h"
#include "cpe/core/draw/Size.h"
#include "cpe/core/terminal.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "WriteHelper.h"
#include "TextFormat.h"
#include "StyledChar.h"

namespace cpe {

//region [ CursorMoving ]

enum class CursorMoving : uint8_t {
    STANDART = 0,
    VERTICAL = 1,
    WRAP = 2,
    REVERSE = 4
};

bool operator==(const CursorMoving &cm, uint8_t i);

bool operator!=(const CursorMoving &cm, uint8_t i);

CursorMoving operator&(const CursorMoving &cm1, const CursorMoving &cm2);

CursorMoving operator|(const CursorMoving &cm1, const CursorMoving &cm2);

//endregion

class TextCanvas : public WriteHelper {
public:

    explicit TextCanvas(const Size &size);

    ~TextCanvas();

    const Point &cursor_position() const;

    void cursor_position(const Point &pos);

    const TextCharStyle &cursor_style() const;

    TextCharStyle &cursor_style();

    void cursor_style(const TextCharStyle &cursorStyle);

    const TextFormat &format() const;

    TextFormat &format();

    void format(const TextFormat &wf);

    const Size & size() const;

    const Size & used_size() const;

    bool have_parent() const;

    const TextCanvas& get_parent() const;

    TextCanvas& get_parent();

    TextCanvas extract(const Point& begin, const Point& size);

    void draw(const std::string &str);

    void draw(const TextCanvas &canvas, bool useActualSize);

    void draw(char character, const CursorMoving& moving = CursorMoving::STANDART);

    void output_to(std::ostream &outStream) const;

    void clear();

    void move_cursor(const Point &vector);

private:
    Point mCursorPos;
    TextCharStyle mCursorStyle;
    TextCharStyle** mMatrix;
    TextCanvas* mParent = nullptr;
    TextFormat mFormat;
    Size mSize;
    Size mUsedSize;

    explicit TextCanvas(TextCanvas* parent);

    inline void _check_size(const Size &size);

    inline void _print_symbol(char c);

    inline void _wrap();

    inline void _layout_cursor();

    inline void _add_lines();
};

}




