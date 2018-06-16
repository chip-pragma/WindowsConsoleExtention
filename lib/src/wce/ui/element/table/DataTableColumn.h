#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include "wce/ui/output/StyledText.h"

namespace wce {

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
    bool visible = true;
    StyledText header;
    TextColor cellColor;
    DataTableColumnSortPredicate<TModel> sortPredicate = nullptr;
};

}




