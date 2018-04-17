#pragma once

#include <cstdint>
#include <vector>

#include "cpe/core/Color.h"

namespace cpe::ui {

using namespace cpe;

template<class TController>
class AView {
public:


protected:


private:
    class OutChar {
    public:
        char symbol = 0;
        core::Color foreColor;
        core::Color backColor;
    };

    using OutCharList = std::vector<OutChar>;
    using OutLineList = std::vector<OutCharList>;

    OutLineList mLines;
};


}