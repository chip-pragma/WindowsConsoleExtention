#include "DataTableColumn.h"

namespace cpe {

DataTableColumn::DataTableColumn(const std::string &caption)
        : mCaption(caption) { }

DataTableColumn::DataTableColumn(const std::string &caption, const TextColor &headerColor)
        : mCaption(caption),
          mHeaderColor(headerColor) { }

DataTableColumn::DataTableColumn(const std::string &caption, const TextColor &headerColor, const TextColor &cellColor)
        : mCaption(caption),
          mHeaderColor(headerColor),
          mCellColor(cellColor) { }

const std::string &DataTableColumn::caption() const {
    return mCaption;
}

std::string &DataTableColumn::caption() {
    return mCaption;
}

const TextColor &DataTableColumn::header_color() const {
    return mHeaderColor;
}

TextColor &DataTableColumn::header_color() {
    return mHeaderColor;
}

const TextColor &DataTableColumn::cell_color() const {
    return mCellColor;
}

TextColor &DataTableColumn::cell_color() {
    return mCellColor;
}

}