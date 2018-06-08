#pragma once

#include <cstdint>
#include <string>
#include <optional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cpe/ui/IModel.h>

namespace cpe {

template<class TDataModel>
class DataTableModel {
public:

    const std::optional<uint32_t> &getSortBy() const;

    void setSortBy(const std::optional<uint32_t> &sortBy);

    const std::optional<std::string> &getFilterBy() const;

    void setFilterBy(const std::optional<std::string> &filterBy);

    const std::optional<size_t> &getPageItemCount() const;

    void setPageItemCount(const std::optional<size_t> &pageItemCount);

    size_t getPageCount() const;

    size_t getPageNumber() const;

    void setPageNumber(size_t pageNumber);

    void setDataSource(const std::vector<TDataModel> &dataSource);

    const std::vector<TDataModel> &getDataSource() const;

    std::vector<TDataModel> apply(const DataTableColumnVector<TDataModel> &columnVec);

private:
    std::optional<uint32_t> mSortBy = std::nullopt;
    std::optional<std::string> mFilterBy = std::nullopt;
    std::optional<size_t> mPageItemCount = std::nullopt;
    size_t mPageCount = 0;
    size_t mPageNumber = 0;

    const std::vector<TDataModel> *mDataSource = nullptr;

};

template<class TDataModel>
const std::optional<uint32_t> &DataTableModel<TDataModel>::getSortBy() const {
    return mSortBy;
}

template<class TDataModel>
void DataTableModel<TDataModel>::setSortBy(const std::optional<uint32_t> &sortBy) {
    mSortBy = sortBy;
}

template<class TDataModel>
const std::optional<std::string> &DataTableModel<TDataModel>::getFilterBy() const {
    return mFilterBy;
}

template<class TDataModel>
void DataTableModel<TDataModel>::setFilterBy(const std::optional<std::string> &filterBy) {
    mFilterBy = filterBy;
}

template<class TDataModel>
const std::optional<size_t> &DataTableModel<TDataModel>::getPageItemCount() const {
    return mPageItemCount;
}

template<class TDataModel>
void DataTableModel<TDataModel>::setPageItemCount(const std::optional<size_t> &pageItemCount) {
    mPageItemCount = pageItemCount;
}

template<class TDataModel>
size_t DataTableModel<TDataModel>::getPageCount() const {
    return mPageCount;
}

template<class TDataModel>
size_t DataTableModel<TDataModel>::getPageNumber() const {
    return mPageNumber;
}

template<class TDataModel>
void DataTableModel<TDataModel>::setPageNumber(size_t pageNumber) {
    mPageNumber = std::clamp(pageNumber, size_t(0), mPageCount);
}

template<class TDataModel>
void DataTableModel<TDataModel>::setDataSource(const std::vector<TDataModel> &dataSource) {
    mDataSource = &dataSource;
}

template<class TDataModel>
const std::vector<TDataModel> &DataTableModel<TDataModel>::getDataSource() const {
    return mDataSource;
}

template<class TDataModel>
std::vector<TDataModel> DataTableModel<TDataModel>::apply(const DataTableColumnVector<TDataModel> &columnVec) {
    std::vector<TDataModel> resultData;
    if (!mDataSource)
        return resultData;

    resultData = *mDataSource;

    if (mFilterBy.has_value()) {
        std::remove_if(
            resultData.begin(),
            resultData.end(),
            [&](const TDataModel &data) {
                auto &model = static_cast<const IModel &>(data);
                for (const DataTableColumnPair<TDataModel> &colPair : columnVec) {
                    std::string fieldValue = "";
                    if (model.getFieldValue(colPair.first, fieldValue))
                        if (fieldValue.find(mFilterBy.value()) != std::string::npos)
                            return false;
                }
                return true;
            });
    }

    if (mSortBy.has_value()) {
        DataTableColumn<TDataModel> *column = nullptr;
        std::find_if(
            columnVec.begin(),
            columnVec.end(),
            [&](const DataTableColumnPair<TDataModel> &pair) {
                bool equal = (pair.first == mSortBy.value());
                if (equal)
                    column = pair.second;
                return equal;
            });
        if (column
            && column->getVisible()
            && column->getSortFunctor())
            std::sort(resultData.begin(), resultData.end(), column->getSortFunctor());
    }

    if (!mPageItemCount.has_value()) {
        mPageCount = 1;
        mPageNumber = 0;
    } else {
        auto items = mPageItemCount.value();
        mPageCount = resultData.size() / items + 1;
        mPageNumber = std::clamp(mPageNumber, size_t(0), mPageCount - 1);

        auto begin = mPageNumber * items;
        auto end = std::min(begin + items, resultData.size());
        resultData = std::vector<TDataModel>(resultData.begin() + begin, resultData.begin() + end);
    }

    return resultData;
}

}




