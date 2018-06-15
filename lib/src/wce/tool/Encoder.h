#pragma once

#include <string>

#include "platform/platform.h"

namespace wce {

class Encoder {
public:
    enum Encoding : uint32_t {
        UTF8 = 65001,
        CP866 = 866,
        CP1551 = 1251
    };

    explicit Encoder(Encoding encodingCp);

    std::wstring from(const std::string &str) const;

    std::string to(const std::wstring &bytes) const;

private:
    Encoding mCp;
};

}
