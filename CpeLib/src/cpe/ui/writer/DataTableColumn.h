#pragma once

#include <cstdint>
#include <string>

#include "cpe/ui/style/TextColor.h"

namespace cpe {

class DataTableColumn {
public:
    DataTableColumn(const std::string &caption);

    DataTableColumn(const std::string &caption, const TextColor &headerColor);

    DataTableColumn(const std::string &caption, const TextColor &headerColor, const TextColor &cellColor);

    const std::string &caption() const;

    std::string &caption();

    const TextColor &header_color() const;

    TextColor &header_color();

    const TextColor &cell_color() const;

    TextColor &cell_color();

protected:
    std::string mCaption;
    TextColor mHeaderColor;
    TextColor mCellColor;
};

}




