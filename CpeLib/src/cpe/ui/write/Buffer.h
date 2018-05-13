#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Color.h"
#include "cpe/core/draw/Point.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextColor.h"
#include "WriteHelper.h"
#include "StyledText.h"
#include "StyledChar.h"

namespace cpe {

class Buffer : public WriteHelper {
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

    Buffer extract(const Point &begin, const Point &size);

    void draw(const StyledText &text);

    void draw_line(const StyledText &str = StyledText());

    void draw(const Buffer &sub, bool useActualSize);

    void draw(StyledChar schar, int32_t count = 1, bool vertical = false);

    void output_to(std::ostream &outStream) const;

    void clear();

    const StyledChar &at(const Point &pos) const;

    StyledChar &at(const Point &pos);

    StyledChar &operator[](const Point &pos);

private:
    Point mCursorPos;
    StyledChar** mBuffer;
    Buffer* mOwner = nullptr;
    Point mSize;
    Point mMaxCurPos;

    explicit Buffer(Buffer *parent, const Point &size);
};

}




