#pragma once

#include <vector>
#include <optional>

#include "IOutputable.h"
#include "StyledChar.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

// FEATURE переделать StyledText, реализовать StyledTextBuilder, удалить StyledString

class StyledText : public IOutputable {
    // QUEST Реализовать нормальные итераторы
public:
    StyledText();

    ~StyledText() override;

    const TextColor& text_color() const;

    StyledText& color(const TextColor &tColor);

    StyledText& reset_color();

    StyledText& append(const std::string &str);

    StyledText& append(const StyledText &sText);

    size_t length() const;

    StyledChar at(size_t index) const;

    void output_to(std::ostream &outStream) const override;

    const std::string& to_string() const;

    StyledChar operator[](size_t index) const;

protected:
    struct _TextColorLine {
        _TextColorLine() = default;

        explicit _TextColorLine(const TextColor &color, size_t pos = 0)
            : color(color),
              position(pos) { }

        TextColor color;
        size_t position = 0;
    };

    std::string mText;
    std::vector<_TextColorLine> mColors;

};

}




