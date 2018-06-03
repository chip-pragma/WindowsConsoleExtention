#pragma once

#include <cstdint>
#include <string>

#include "cpe/ui/output/StyledText.h"

namespace cpe {

class DataTableColumn {
public:

    bool getVisible() const;

    void setVisible(bool vis);

    const StyledText &getHeader() const;

    StyledText &getHeader();

    const TextColor &getCellTextColor() const;

    TextColor &getCellTextColor();

protected:
    bool mVisible = true;
    StyledText mHeader;
    TextColor mCellColor;
};

}




