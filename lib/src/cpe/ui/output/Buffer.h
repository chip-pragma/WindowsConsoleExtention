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

namespace wce {

class Buffer : public IOutputable {
public:

    explicit Buffer(const Point &size);

    ~Buffer() override;

    const Point &getCursorPos() const;

    Point &getCursorPosRef();

    const Point & getSize() const;

    Point getUsedSize() const;

    const uint8_t &getTabLength() const;

    uint8_t &getTabLengthRef();

    const std::string &getUnfinished() const;

    std::string &getUnfinishedRef();

    bool hasOwner() const;

    const Buffer& getOwner() const;

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
    void printChar(const StyledChar &schar);
    // Печатает текстовый символ (с пропуском строки и т.п.)
    void printTextChar(const StyledChar &schar);
    // Расчет максимальной позиции курсора
    void getPointWithMaxCrd();
};

}




