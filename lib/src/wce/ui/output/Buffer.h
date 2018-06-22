#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#include "wce/core/console.h"
#include "wce/core/graphics/Point.h"
#include "wce/ui/style/TextColor.h"
#include "IOutputable.h"
#include "OutputHelper.h"
#include "StyledChar.h"
#include "StyledText.h"

namespace wce {

class Buffer : public IOutputable {
public:
    uint8_t tabLength = 5;
    std::string unfinished = "<~>";
    Point cursorPosition;

    explicit Buffer(const Point &size);

    ~Buffer() override;

    const Point &getSize() const;

    Point getUsedSize() const;

    bool hasOwner() const;

    const Buffer &getOwner() const;

    Buffer extract(Point begin, Point size, bool clean = true);

    void draw(const StyledText &text, bool softWrap = true);

    void drawLine(const StyledText &str, bool softWrap = true);

    void draw(const Buffer &sub, bool useActualSize);

    void draw(StyledChar schar, int32_t count = 1, bool vertical = false);

    void outputTo(std::ostream &outStream) const override;

    void clear();

    const StyledChar &at(const Point &pos) const;

    StyledChar &at(const Point &pos);

    StyledChar &operator[](const Point &pos);

private:
    StyledChar **m_buffer;
    Buffer *m_owner = nullptr;
    Point m_beginPosFromOwner;
    Point m_size;
    Point m_maxCurPos;

    explicit Buffer(Buffer *parent, const Point &beginPos, const Point &size);

    // "Печатает" символ в допустимой области холста
    void printChar(const StyledChar &schar);

    // Печатает текстовый символ (с пропуском строки и т.п.)
    void printTextChar(const StyledChar &schar);

    // Расчет максимальной позиции курсора
    void getPointWithMaxCrd();
};

}




