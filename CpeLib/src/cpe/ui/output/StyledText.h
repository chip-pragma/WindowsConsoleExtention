#pragma once

#include <vector>

#include "IOutputable.h"
#include "StyledChar.h"
#include "StyledString.h"

namespace cpe {

class StyledText : public IOutputable, public std::vector<StyledChar> {
    using _BaseVector = std::vector<StyledChar>;
public:
    StyledText() = default;

    StyledText(const StyledString &sStr);

    StyledText(uint8_t tabLength, const std::string &unf);

    ~StyledText() override;

    const uint8_t &tab_length() const;

    uint8_t &tab_length();

    const std::string &unfinished() const;

    std::string &unfinished();

    void push_back(const std::string &str);

    void push_back(const StyledString &sStr);

    void push_back(const StyledText &sText);

    void output_to(std::ostream &outStream) const override;

protected:
    uint8_t mTabLength = 5;
    std::string mUnfinished = "<~>";
};

}




