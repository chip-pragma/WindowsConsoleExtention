#pragma once

#include <string>

#include "IOutputable.h"
#include "cpe/ui/style/TextColor.h"


namespace cpe {

class StyledString : public IOutputable {
public:
    StyledString() = default;

    StyledString(const std::string &text);

    StyledString(const std::string &text, const TextColor &color);

    const TextColor &color() const;

    TextColor &color();

    const std::string &str() const;

    std::string &str();

    void output_to(std::ostream &outStream) const override;

private:
    TextColor mColor;
    std::string mString;
};

}
