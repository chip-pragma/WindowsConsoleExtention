#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include "cpe/ui/output/StyledText.h"

namespace cpe {

template<class TDataModel>
class DataTableColumn;

template<class TDataModel>
using DataTableColumnPair = std::pair<uint32_t, DataTableColumn<TDataModel> *>;
template<class TDataModel>
using DataTableColumnVector = std::vector<DataTableColumnPair<TDataModel>>;
template<class TDataModel>
using DataTableColumnSortPredicate = std::function<bool(const TDataModel &, const TDataModel &)>;

template<class TDataModel>
class DataTableColumn {
public:

    bool getVisible() const;

    void setVisible(bool vis);

    const StyledText &getHeader() const;

    StyledText &getHeader();

    const TextColor &getCellTextColor() const;

    TextColor &getCellTextColor();

    const DataTableColumnSortPredicate<TDataModel> &getSortFunctor() const;

    void setSortFunctor(const DataTableColumnSortPredicate<TDataModel> &sortFunctor);

protected:
    bool mVisible = true;
    StyledText mHeader;
    TextColor mCellColor;
    DataTableColumnSortPredicate<TDataModel> mSortFunctor = nullptr;
};

template<class TDataModel>
bool DataTableColumn<TDataModel>::getVisible() const {
    return mVisible;
}

template<class TDataModel>
void DataTableColumn<TDataModel>::setVisible(bool vis) {
    mVisible = vis;
}

template<class TDataModel>
const StyledText &DataTableColumn<TDataModel>::getHeader() const {
    return mHeader;
}

template<class TDataModel>
StyledText &DataTableColumn<TDataModel>::getHeader() {
    return mHeader;
}

template<class TDataModel>
const TextColor &DataTableColumn<TDataModel>::getCellTextColor() const {
    return mCellColor;
}

template<class TDataModel>
TextColor &DataTableColumn<TDataModel>::getCellTextColor() {
    return mCellColor;
}

template<class TDataModel>
const DataTableColumnSortPredicate<TDataModel> &DataTableColumn<TDataModel>::getSortFunctor() const {
    return mSortFunctor;
}

template<class TDataModel>
void DataTableColumn<TDataModel>::setSortFunctor(const DataTableColumnSortPredicate<TDataModel> &sortFunctor) {
    mSortFunctor = sortFunctor;
}

}




