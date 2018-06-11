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

    StyledText &getHeader();

    const TextColor &getCellTextColor() const;

    TextColor &getCellTextColor();

    const DataTableColumnSortPredicate<TModel> &getSortFunctor() const;

    void setSortFunctor(const DataTableColumnSortPredicate<TModel> &sortFunctor);

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
StyledText &DataTableColumn<TModel>::getHeader() {
    return mHeader;
}

template<class TModel>
const TextColor &DataTableColumn<TModel>::getCellTextColor() const {
    return mCellColor;
}

template<class TModel>
TextColor &DataTableColumn<TModel>::getCellTextColor() {
    return mCellColor;
}

template<class TModel>
const DataTableColumnSortPredicate<TModel> &DataTableColumn<TModel>::getSortFunctor() const {
    return mSortFunctor;
}

template<class TModel>
void DataTableColumn<TModel>::setSortFunctor(const DataTableColumnSortPredicate<TModel> &sortFunctor) {
    mSortFunctor = sortFunctor;
}

}




