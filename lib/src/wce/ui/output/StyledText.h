#pragma once

#include <vector>
#include <optional>

#include "IOutputable.h"
#include "StyledChar.h"
#include "wce/ui/style/TextColor.h"

namespace wce {

class StyledText : public IOutputable {
    // TODO Реализовать нормальные итераторы
public:
    StyledText();

    ~StyledText() override;

    const TextColor &getColor() const;

    StyledText &setColor(const TextColor &tColor);

    StyledText &setFore(const ColorIndex &fore);

    StyledText &setBack(const ColorIndex &back);

    StyledText &resetColor();

    StyledText &append(const std::string &str);

    StyledText &append(const StyledText &sText);

    StyledText &append(const StyledChar &sChar);

    StyledText &clear();

    size_t getLength() const;

    StyledChar at(size_t index) const;

    void outputTo(std::ostream &outStream) const override;

    const std::string &toString() const;

    StyledChar operator[](size_t index) const;

    StyledText operator+(const std::string &str);

    StyledText operator+(const StyledText &sText);

    StyledText operator+(const StyledChar &sChar);

    StyledText& operator+=(const std::string &str);

    StyledText& operator+=(const StyledText &sText);

    StyledText& operator+=(const StyledChar &sChar);

protected:
    struct _TextColorLine {
        _TextColorLine() = default;

        explicit _TextColorLine(const TextColor &color, size_t pos, size_t length = 0)
            : color(color),
              position(pos),
              length(length) { }

        TextColor color;
        size_t position = 0;
        size_t length = 0;
    };

    std::string m_text;
    std::vector<_TextColorLine> m_colors;

};

StyledText operator+(const StyledChar &sc1, const StyledChar &sc2);
}




