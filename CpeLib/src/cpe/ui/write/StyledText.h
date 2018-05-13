#pragma once

#include <string>

#include "cpe/ui/style/TextColor.h"

namespace cpe {

class StyledText {
public:
    StyledText() = default;

    explicit StyledText(const std::string &text);

    StyledText(const std::string &text, const TextColor &color);

    StyledText(const std::string &text, const TextColor &color, uint8_t tabLength, const std::string &unf);

    const TextColor &color() const;

    TextColor &color();

    void color(const TextColor &color);

    const std::string &text() const;

    std::string &text();

    void text(const std::string &text);

    uint8_t tab_length() const;

    void tab_length(uint8_t tabLength);

    const std::string &unfinished() const;

    void unfinished(const std::string &unfinished);

private:
    TextColor mColor;
    std::string mText;
    uint8_t mTabLength = 5;
    std::string mUnfinished = "<~>";
};

}
