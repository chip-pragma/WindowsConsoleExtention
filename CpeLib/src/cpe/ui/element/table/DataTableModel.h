#pragma once

#include <cstdint>
#include <string>
#include <optional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cpe/ui/IModel.h>

namespace cpe {

template<class TData>
class DataTableModel {
public:
    DataTableModel(const std::vector<TData> &dataSource);

    const std::optional<uint32_t> &getSortBy() const;

    void setSortBy(const std::optional<uint32_t> &sortBy);

    const std::optional<std::string> &getFilterBy() const;

    void setFilterBy(const std::optional<std::string> &filterBy);

    const std::optional<size_t> &getPageItemCount() const;

    void setPageItemCount(const std::optional<size_t> &pageItemCount);

    size_t getPageCount() const;

    size_t getPageNumber() const;

    void setPageNumber(size_t pageNumber);

    const std::vector<TData> &getDataSource() const;

    std::vector<TData> apply();

private:
    std::optional<uint32_t> mSortBy = std::nullopt;
    std::optional<std::string> mFilterBy = std::nullopt;
    std::optional<size_t> mPageItemCount = std::nullopt;
    size_t mPageCount = 0;
    size_t mPageNumber = 0;

    const std::vector<TData> &mDataSource;

};

template<class TData>
DataTableModel<TData>::DataTableModel(const std::vector<TData> &dataSource)
    : mDataSource(dataSource) { }

template<class TData>
const std::optional<uint32_t> &DataTableModel<TData>::getSortBy() const {
    return mSortBy;
}

template<class TData>
void DataTableModel<TData>::setSortBy(const std::optional<uint32_t> &sortBy) {
    mSortBy = sortBy;
}

template<class TData>
const std::optional<std::string> &DataTableModel<TData>::getFilterBy() const {
    return mFilterBy;
}

template<class TData>
void DataTableModel<TData>::setFilterBy(const std::optional<std::string> &filterBy) {
    mFilterBy = filterBy;
}

template<class TData>
const std::optional<size_t> &DataTableModel<TData>::getPageItemCount() const {
    return mPageItemCount;
}

template<class TData>
void DataTableModel<TData>::setPageItemCount(const std::optional<size_t> &pageItemCount) {
    mPageItemCount = pageItemCount;
}

template<class TData>
size_t DataTableModel<TData>::getPageCount() const {
    return mPageCount;
}

template<class TData>
size_t DataTableModel<TData>::getPageNumber() const {
    return mPageNumber;
}

template<class TData>
void DataTableModel<TData>::setPageNumber(size_t pageNumber) {
    mPageNumber = std::clamp(pageNumber, size_t(0), mPageCount);
}

template<class TData>
const std::vector<TData> &DataTableModel<TData>::getDataSource() const {
    return mDataSource;
}

template<class TData>
std::vector<TData> DataTableModel<TData>::apply() {
    std::vector<TData> result;
    result = mDataSource;

    if (mSortBy.has_value()) {
        std::sort(result.begin(),
                  result.end(),
                  [=](const TData &oneData, const TData &twoData) -> bool {
                      auto &oneModel = static_cast<const IModel &>(oneData);
                      auto &twoModel = static_cast<const IModel &>(twoData);

                      std::string oneFieldValue;
                      std::string twoFieldValue;
                      oneModel.getFieldValue(mSortBy.value(), oneFieldValue);
                      twoModel.getFieldValue(mSortBy.value(), twoFieldValue);

                      return (oneFieldValue.compare(twoFieldValue) < 0);
                  }
        );
    }

    // TODO фильтрация (поиск) mFilterBy

    if (!mPageItemCount.has_value()) {
        mPageCount = 1;
        mPageNumber = 0;
    } else {
        auto items = mPageItemCount.value();
        mPageCount = result.size() / items + 1;
        mPageNumber = std::clamp(mPageNumber, size_t(0), mPageCount - 1);

        auto begin = mPageNumber * items;
        auto end = std::min(begin + items, result.size());
        result = std::vector<TData>(result.begin() + begin, result.begin() + end);
    }

    return result;
}

}




