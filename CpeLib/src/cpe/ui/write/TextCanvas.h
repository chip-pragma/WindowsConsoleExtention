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

    void move_cursor(const Point &vector);

    const TextCharStyle &cursor_style() const;

    TextCharStyle &cursor_style();

    void cursor_style(const TextCharStyle &cursorStyle);

    const TextFormat &format() const;

    TextFormat &format();

    void format(const TextFormat &wf);

    const Size & size() const;

    Size calc_used_size() const;

    bool have_owner() const;

    const TextCanvas& owner() const;

    TextCanvas& owner();

    TextCanvas extract(const Point &begin, const Size &size);

    void draw(const std::string &str);

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
    Size mSize;
    Point mMaxCurPos;

    explicit TextCanvas(TextCanvas *parent, const Size &size);

    inline void __check_size(const Size &size);

    inline void __print_char(char c);

    inline void __print_text_char(char c);

    inline void __new_line();

    inline void __max_cursor_position();

    inline Point __get_clamped_max_cur_pos() const;

    inline bool __check_size_limits(const Point &point) const;
};

}




