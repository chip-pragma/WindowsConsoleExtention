#include "DataTableColumn.h"

namespace cpe {

bool DataTableColumn::getVisible() const {
    return mVisible;
}

void DataTableColumn::setVisible(bool vis) {
    mVisible = vis;
}

const StyledText &DataTableColumn::getHeader() const {
    return mHeader;
}

StyledText &DataTableColumn::getHeader() {
    return mHeader;
}

const TextColor &DataTableColumn::getCellTextColor() const {
    return mCellColor;
}

TextColor &DataTableColumn::getCellTextColor() {
    return mCellColor;
}

}