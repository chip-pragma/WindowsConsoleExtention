#pragma once

#include <vector>
#include <optional>

#include "IOutputable.h"
#include "StyledChar.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

class StyledText : public IOutputable {
    // QUEST Реализовать нормальные итераторы
public:
    StyledText();

    ~StyledText() override;

    const TextColor& getColor() const;

    StyledText& setColor(const TextColor &tColor);

    StyledText& setFore(const Color& fore);

    StyledText& setBack(const Color& back);

    StyledText& resetColor();

    StyledText& append(const std::string &str);

    StyledText& append(const StyledText &sText);

    size_t getLength() const;

    StyledChar at(size_t index) const;

    void outputTo(std::ostream &outStream) const override;

    const std::string& toString() const;

    StyledChar operator[](size_t index) const;

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

    std::string mText;
    std::vector<_TextColorLine> mColors;

};

}




