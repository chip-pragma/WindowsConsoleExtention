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
#include "StyledText.h"

namespace cpe {

class Buffer : public IOutputable {
public:

    explicit Buffer(const Point &size);

    ~Buffer() override;

    const Point &cursor_position() const;

    Point &cursor_position();

    const Point & get_size() const;

    Point get_used_size() const;

    const uint8_t &tab_length() const;

    uint8_t &tab_length();

    const std::string &unfinished() const;

    std::string &unfinished();

    bool has_owner() const;

    const Buffer& get_owner() const;

    Buffer extract(Point begin, Point size, bool clean = true);

    void draw(const StyledText &text, bool softWrap = true);

    void draw_line(const StyledText &str, bool softWrap = true);

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
    uint8_t mTabLength = 5;
    std::string mUnfinished = "<~>";

    explicit Buffer(Buffer *parent, const Point &beginPos, const Point &size);

    // "Печатает" символ в допустимой области холста
    void __print_char(const StyledChar &schar);
    // Печатает текстовый символ (с пропуском строки и т.п.)
    void __print_text(const StyledChar &schar);
    // Расчет максимальной позиции курсора
    void __point_with_max_crd();
};

}




