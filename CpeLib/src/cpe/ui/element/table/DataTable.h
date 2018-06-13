#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <optional>
#include <algorithm>

#include "cpe/core/Exception.h"
#include "cpe/ui/BaseWriter.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/IModel.h"
#include "DataTableColumn.h"

namespace cpe {

template<class TModel>
class DataTable : public BaseWriter<DataTable<TModel>> {
public:
    ~DataTable() override;

    const StyledBorder &getBorder() const;

    StyledBorder &getBorderRef();

    const std::optional<uint32_t> &getSortBy() const;

    void setSortBy(const std::optional<uint32_t> &sortBy);

    const std::optional<std::string> &getFilterBy() const;

    void setFilterBy(const std::optional<std::string> &filterBy);

    const std::optional<size_t> &getPageItemCount() const;

    void setPageItemCount(const std::optional<size_t> &pageItemCount);

    size_t getPageCount() const;

    size_t getPageNumber() const;

    void setPageNumber(size_t pageNumber);

    template<class TColumn, class ...Args>
    TColumn &makeColumn(uint32_t fieldId, Args ...args);

    bool removeColumn(uint32_t fieldId);

    bool tryGetColumn(uint32_t fieldId, DataTableColumn<TModel> &outColumn) const;

    void setDataSource(const std::vector<TModel> &dataSource);

    const std::vector<TModel> &getDataSource() const;

protected:
    StyledBorder mBorder;
    DataTableColumnVector<TModel> mColumns;
    std::optional<uint32_t> mSortBy = std::nullopt;
    std::optional<std::string> mFilterBy = std::nullopt;
    std::optional<size_t> mPageItemCount = std::nullopt;
    size_t mPageCount = 0;
    size_t mPageNumber = 0;
    const std::vector<TModel> *mDataSource = nullptr;

    void onWrite(Buffer &buf) override;

    void prepareData(std::vector<TModel> &modifiedData);
};

template<class TModel>
DataTable<TModel>::~DataTable() {
    for (DataTableColumnPair<TModel> col : mColumns)
        delete col.second;
}

template<class TModel>
const StyledBorder &DataTable<TModel>::getBorder() const {
    return mBorder;
}

template<class TModel>
StyledBorder &DataTable<TModel>::getBorderRef() {
    return mBorder;
}


template<class TModel>
const std::optional<uint32_t> &DataTable<TModel>::getSortBy() const {
    return mSortBy;
}

template<class TModel>
void DataTable<TModel>::setSortBy(const std::optional<uint32_t> &sortBy) {
    mSortBy = sortBy;
}

template<class TModel>
const std::optional<std::string> &DataTable<TModel>::getFilterBy() const {
    return mFilterBy;
}

template<class TModel>
void DataTable<TModel>::setFilterBy(const std::optional<std::string> &filterBy) {
    mFilterBy = filterBy;
}

template<class TModel>
const std::optional<size_t> &DataTable<TModel>::getPageItemCount() const {
    return mPageItemCount;
}

template<class TModel>
void DataTable<TModel>::setPageItemCount(const std::optional<size_t> &pageItemCount) {
    mPageItemCount = pageItemCount;
}

template<class TModel>
size_t DataTable<TModel>::getPageCount() const {
    return mPageCount;
}

template<class TModel>
size_t DataTable<TModel>::getPageNumber() const {
    return mPageNumber;
}

template<class TModel>
void DataTable<TModel>::setPageNumber(size_t pageNumber) {
    mPageNumber = std::clamp(pageNumber, size_t(0), mPageCount);
}

template<class TModel>
template<class TColumn, class... Args>
TColumn &DataTable<TModel>::makeColumn(uint32_t fieldId, Args... args) {
    bool anyOf = std::any_of(
        mColumns.cbegin(), mColumns.cend(),
        [&](const DataTableColumnPair<TModel> &pair) {
            return pair.first == fieldId;
        });
    if (anyOf)
        throw Exception("ID already in use");

    auto column = static_cast<DataTableColumn<TModel> *>(new TColumn());
    mColumns.emplace_back(fieldId, column);
    return *column;
}

template<class TModel>
bool DataTable<TModel>::removeColumn(uint32_t fieldId) {
    auto find = std::find_if(
        mColumns.cbegin(), mColumns.cend(),
        [&](const DataTableColumnPair<TModel> &pair) {
            return pair.first == fieldId;
        });
    if (find != mColumns.cend()) {
        mColumns.erase(find);
        return true;
    }
    return false;
}

template<class TModel>
bool DataTable<TModel>::tryGetColumn(uint32_t fieldId, DataTableColumn<TModel> &outColumn) const {
    auto iter = std::find_if(mColumns.begin(),
                             mColumns.end(),
                             [&](const DataTableColumnPair<TModel> &pair) {
                                 bool equal = (pair.first == fieldId);
                                 if (equal)
                                     outColumn = *(pair.second);
                                 return equal;
                             }
    );
    return (iter != mColumns.end());
}

template<class TModel>
void DataTable<TModel>::setDataSource(const std::vector<TModel> &dataSource) {
    mDataSource = &dataSource;
}

template<class TModel>
const std::vector<TModel> &DataTable<TModel>::getDataSource() const {
    return mDataSource;
}

template<class TModel>
void DataTable<TModel>::onWrite(Buffer &buf) {
    struct ExtColumn {
        uint32_t id;
        DataTableColumn<TModel> *column;
        int width;
    };
    std::vector<ExtColumn> extColsVec;

    const int offset = 1;
    int curColDrawPos = offset;
    int maxCellHeight = 0;

    //region [ HEADER ]
    auto srcColsCount = static_cast<int>(mColumns.size());
    int colDrawWidth = buf.getSize().getX() - srcColsCount;

    for (DataTableColumnPair<TModel> &colPair : mColumns) {
        ExtColumn extCol{
            extCol.id = colPair.first,
            extCol.column = colPair.second
        };

        extCol.width = static_cast<int>(std::round(colDrawWidth / srcColsCount--));
        colDrawWidth -= extCol.width;
        extColsVec.push_back(extCol);

        auto colHeaderBuf = buf.extract(
            Point(curColDrawPos, 0),
            Point(extCol.width, buf.getSize().getY()));
        colHeaderBuf.draw(extCol.column->getHeaderRef());

        curColDrawPos += extCol.width + 1;
        maxCellHeight = std::max(maxCellHeight, colHeaderBuf.getUsedSize().getYRef());
    }

    //endregion

    //region [ HEADER UNDERLINE ]
    buf.getCursorPosRef() = Point(offset, maxCellHeight);

    for (size_t i = 0, n = -1 + extColsVec.size(); i <= n; i++) {
        const StyledBorder &bord = this->getBorderRef();
        ExtColumn &extCol = extColsVec.at(i);

        buf.draw(bord.at(BorderStyle::ST), extCol.width);
        if (i < n)
            buf.draw(bord.at(BorderStyle::STV));
    }

    maxCellHeight += 1;

    //endregion

    std::vector<TModel> dataModelList;
    this->prepareData(dataModelList);
    int usedHeight = 0;
    for (size_t i = 0, n = -1 + dataModelList.size(); i <= n; i++) {
        auto &srcDataItem = static_cast<const IModel &>(dataModelList.at(i));

        usedHeight += maxCellHeight;
        maxCellHeight = 0;

        //region [ CELL ]

        curColDrawPos = offset;

        for (ExtColumn &extColPair : extColsVec) {
            if (!extColPair.column->getVisible())
                continue;

            auto cellBuf = buf.extract(
                Point(curColDrawPos, usedHeight),
                Point(extColPair.width, buf.getSize().getY() - usedHeight));

            StyledText modelDataStr;
            std::string modelDataField;
            if (srcDataItem.tryGetFieldValue(extColPair.id, modelDataField)) {
                modelDataStr
                    .setColor(extColPair.column->getCellTextColorRef())
                    .append(modelDataField);
            }
            cellBuf.draw(modelDataStr);

            curColDrawPos += extColPair.width + 1;
            maxCellHeight = std::max(maxCellHeight, cellBuf.getUsedSize().getYRef());
        }

        //endregion

        //region [ GRID ]

        buf.getCursorPosRef() = Point(offset, usedHeight + maxCellHeight);
        for (size_t j = 0, m = -1 + extColsVec.size(); j <= m; j++) {
            ExtColumn &extCol = extColsVec.at(j);

            buf.draw(mBorder.at(BorderStyle::SH), extCol.width);
            if (j < m) {
                buf.getCursorPosRef().getYRef() = usedHeight;
                buf.draw(mBorder.at(BorderStyle::SV), maxCellHeight, true);

                if (i < n)
                    buf.draw(mBorder.at(BorderStyle::SC));
                else
                    buf.draw(mBorder.at(BorderStyle::SBV));
            }
        }

        //endregion

        usedHeight += 1;
    }
}


template<class TModel>
void DataTable<TModel>::prepareData(std::vector<TModel> &modifiedData) {
    if (!mDataSource)
        return;

    modifiedData.insert(modifiedData.cend(), mDataSource->begin(), mDataSource->end());

    if (mFilterBy.has_value()) {
        std::remove_if(
            modifiedData.begin(),
            modifiedData.end(),
            [&](const TModel &data) {
                auto &model = static_cast<const IModel &>(data);
                for (const DataTableColumnPair<TModel> &colPair : mColumns) {
                    std::string fieldValue = "";
                    if (model.tryGetFieldValue(colPair.first, fieldValue))
                        if (fieldValue.find(mFilterBy.value()) != std::string::npos)
                            return false;
                }
                return true;
            });
    }

    if (mSortBy.has_value()) {
        DataTableColumn<TModel> column;
        auto sortBy = mSortBy.value();
        if (this->tryGetColumn(sortBy, column)
            && column.getVisible()) {
            if (column.getSortPredicate() != nullptr) {
                std::sort(modifiedData.begin(), modifiedData.end(), column.getSortPredicate());
            } else {
                std::sort(
                    modifiedData.begin(), modifiedData.end(),
                    [&](const TModel &c1, const TModel &c2) -> bool {
                        auto &model1 = static_cast<const IModel &>(c1);
                        auto &model2 = static_cast<const IModel &>(c2);
                        std::string f1, f2;
                        if (model1.tryGetFieldValue(sortBy, f1)
                            && model2.tryGetFieldValue(sortBy, f2)) {
                            return f1.compare(f2) < 0;
                        }
                        return false;
                    });
            }
        }
    }

    if (!mPageItemCount.has_value()) {
        mPageCount = 1;
        mPageNumber = 0;
    } else {
        auto items = mPageItemCount.value();
        mPageCount = modifiedData.size() / items + 1;
        mPageNumber = std::clamp(mPageNumber, size_t(0), mPageCount - 1);

        auto begin = mPageNumber * items;
        auto end = std::min(begin + items, modifiedData.size());
        modifiedData = std::vector<TModel>(modifiedData.begin() + begin, modifiedData.begin() + end);
    }
}


}



