#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include "cpe/ui/output/StyledText.h"

namespace cpe {

template<class TModel>
class DataTableColumn;

template<class TModel>
using DataTableColumnPair = std::pair<uint32_t, DataTableColumn<TModel> *>;
template<class TModel>
using DataTableColumnVector = std::vector<DataTableColumnPair<TModel>>;
template<class TModel>
using DataTableColumnSortPredicate = std::function<bool(const TModel &, const TModel &)>;

template<class TModel>
class DataTableColumn {
public:

    bool getVisible() const;

    void setVisible(bool vis);

    const StyledText &getHeader() const;

    StyledText &getHeaderRef();

    const TextColor &getCellTextColor() const;

    TextColor &getCellTextColorRef();

    const DataTableColumnSortPredicate<TModel> &getSortPredicate() const;

    void setSortPredicate(const DataTableColumnSortPredicate<TModel> &sortPredicate);

protected:
    bool mVisible = true;
    StyledText mHeader;
    TextColor mCellColor;
    DataTableColumnSortPredicate<TModel> mSortFunctor = nullptr;
};

template<class TModel>
bool DataTableColumn<TModel>::getVisible() const {
    return mVisible;
}

template<class TModel>
void DataTableColumn<TModel>::setVisible(bool vis) {
    mVisible = vis;
}

template<class TModel>
const StyledText &DataTableColumn<TModel>::getHeader() const {
    return mHeader;
}

template<class TModel>
StyledText &DataTableColumn<TModel>::getHeaderRef() {
    return mHeader;
}

template<class TModel>
const TextColor &DataTableColumn<TModel>::getCellTextColor() const {
    return mCellColor;
}

template<class TModel>
TextColor &DataTableColumn<TModel>::getCellTextColorRef() {
    return mCellColor;
}

template<class TModel>
const DataTableColumnSortPredicate<TModel> &DataTableColumn<TModel>::getSortPredicate() const {
    return mSortFunctor;
}

template<class TModel>
void DataTableColumn<TModel>::setSortPredicate(const DataTableColumnSortPredicate<TModel> &sortPredicate) {
    mSortFunctor = sortPredicate;
}

}




