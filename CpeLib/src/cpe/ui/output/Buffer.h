#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Color.h"
#include "cpe/core/draw/Point.h"
#include "cpe/ui/style/TextColor.h"
#include "IOutputable.h"
#include "OutputHelper.h"
#include "StyledChar.h"
#include "StyledString.h"
#include "StyledText.h"

namespace cpe {

class Buffer : public IOutputable {
public:

    explicit Buffer(const Point &size);

    ~Buffer();

    const Point &cursor_position() const;

    void cursor_position(const Point &pos);

    void move_cursor(const Point &vector);

    const Point & size() const;

    Point calc_used_size() const;

    bool have_owner() const;

    const Buffer& owner() const;

    Buffer& owner();

    Buffer extract(const Point &begin, const Point &size, bool clean = true);

    void draw(const StyledText &text);

    void draw_line(const StyledText &str = StyledString());

    void draw(const Buffer &sub, bool useActualSize);

    void draw(StyledChar schar, int32_t count = 1, bool vertical = false);

    void output_to(std::ostream &outStream) const override;

    void clear();

    const StyledChar &at(const Point &pos) const;

    StyledChar &at(const Point &pos);

    StyledChar &operator[](const Point &pos);

private:
    Point mCursorPos;
    StyledChar** mBuffer;
    Buffer* mOwner = nullptr;
    Point mBeginPosFromOwner;
    Point mSize;
    Point mMaxCurPos;

    explicit Buffer(Buffer *parent, const Point &beginPos, const Point &size);

    // "Печатает" символ в допустимой области холста
    void __print_char(const StyledChar &schar);
    // Печатает текстовый символ (с пропуском строки и т.п.)
    void __print_text(const StyledChar &schar);
    // Расчет максимальной позиции курсора
    void __point_with_max_crd();
};

}




