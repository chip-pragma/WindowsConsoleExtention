#pragma once

#include <string>

namespace cpe {

class TextFormat {
public:
    uint8_t getTabLength() const;

    void setTabLength(uint8_t tabLength);

    const std::string &getUnfinished() const;

    void setUnfinished(const std::string &unfinished);

private:
    uint8_t _tabLength = 10;
    std::string _unfinished = "<...>";
};

}
