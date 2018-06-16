#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <optional>
#include <algorithm>

#include "wce/core/Exception.h"
#include "wce/ui/BaseWriter.h"
#include "wce/ui/output/StyledBorder.h"
#include "wce/ui/IModel.h"
#include "DataTableColumn.h"

namespace wce {

template<class TModel>
class DataTable : public BaseWriter<DataTable<TModel>> {
public:
    StyledBorder border;
    std::optional<uint32_t> sortBy = std::nullopt;
    std::optional<std::string> filterBy = std::nullopt;
    std::optional<size_t> pageItemCount = std::nullopt;
    size_t pageNumber = 0;

    ~DataTable() override;

    size_t getPageCount() const;

    template<class TColumn, class ...Args>
    TColumn &makeColumn(uint32_t fieldId, Args ...args);

    bool removeColumn(uint32_t fieldId);

    bool tryGetColumn(uint32_t fieldId, DataTableColumn<TModel> &outColumn) const;

    void setDataSource(const std::vector<TModel> &dataSource);

    const std::vector<TModel> &getDataSource() const;

protected:
    DataTableColumnVector<TModel> m_columns;
    size_t m_pageCount = 0;

    const std::vector<TModel> *m_dataSource = nullptr;

    void onWrite(Buffer &buf) override;

    void prepareData(std::vector<TModel> &modifiedData);
};

template<class TModel>
DataTable<TModel>::~DataTable() {
    for (DataTableColumnPair<TModel> col : m_columns)
        delete col.second;
}

template<class TModel>
size_t DataTable<TModel>::getPageCount() const {
    return m_pageCount;
}

template<class TModel>
template<class TColumn, class... Args>
TColumn &DataTable<TModel>::makeColumn(uint32_t fieldId, Args... args) {
    bool anyOf = std::any_of(
        m_columns.cbegin(), m_columns.cend(),
        [&](const DataTableColumnPair<TModel> &pair) {
            return pair.first == fieldId;
        });
    if (anyOf)
        throw Exception("ID already in use");

    auto column = static_cast<DataTableColumn<TModel> *>(new TColumn());
    m_columns.emplace_back(fieldId, column);
    return *column;
}

template<class TModel>
bool DataTable<TModel>::removeColumn(uint32_t fieldId) {
    auto find = std::find_if(
        m_columns.cbegin(), m_columns.cend(),
        [&](const DataTableColumnPair<TModel> &pair) {
            return pair.first == fieldId;
        });
    if (find != m_columns.cend()) {
        m_columns.erase(find);
        return true;
    }
    return false;
}

template<class TModel>
bool DataTable<TModel>::tryGetColumn(uint32_t fieldId, DataTableColumn<TModel> &outColumn) const {
    auto iter = std::find_if(m_columns.begin(),
                             m_columns.end(),
                             [&](const DataTableColumnPair<TModel> &pair) {
                                 bool equal = (pair.first == fieldId);
                                 if (equal)
                                     outColumn = *(pair.second);
                                 return equal;
                             }
    );
    return (iter != m_columns.end());
}

template<class TModel>
void DataTable<TModel>::setDataSource(const std::vector<TModel> &dataSource) {
    m_dataSource = &dataSource;
}

template<class TModel>
const std::vector<TModel> &DataTable<TModel>::getDataSource() const {
    return m_dataSource;
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
    auto srcColsCount = static_cast<int>(m_columns.size());
    int colDrawWidth = buf.getSize().x - srcColsCount;

    for (DataTableColumnPair<TModel> &colPair : m_columns) {
        ExtColumn extCol{
            extCol.id = colPair.first,
            extCol.column = colPair.second
        };

        extCol.width = static_cast<int>(std::round(colDrawWidth / srcColsCount--));
        colDrawWidth -= extCol.width;
        extColsVec.push_back(extCol);

        auto colHeaderBuf = buf.extract(
            Point(curColDrawPos, 0),
            Point(extCol.width, buf.getSize().y));
        colHeaderBuf.draw(extCol.column->header);

        curColDrawPos += extCol.width + 1;
        maxCellHeight = std::max(maxCellHeight, colHeaderBuf.getUsedSize().y);
    }

    //endregion

    //region [ HEADER UNDERLINE ]
    buf.cursorPosition = Point(offset, maxCellHeight);

    for (size_t i = 0, n = -1 + extColsVec.size(); i <= n; i++) {
        const StyledBorder &bord = this->border;
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
            if (!extColPair.column->visible)
                continue;

            auto cellBuf = buf.extract(
                Point(curColDrawPos, usedHeight),
                Point(extColPair.width, buf.getSize().y - usedHeight));

            StyledText modelDataStr;
            std::string modelDataField;
            if (srcDataItem.tryGetFieldValue(extColPair.id, modelDataField)) {
                modelDataStr
                    .setColor(extColPair.column->cellColor)
                    .append(modelDataField);
            }
            cellBuf.draw(modelDataStr);

            curColDrawPos += extColPair.width + 1;
            maxCellHeight = std::max(maxCellHeight, cellBuf.getUsedSize().y);
        }

        //endregion

        //region [ GRID ]

        buf.cursorPosition = Point(offset, usedHeight + maxCellHeight);
        for (size_t j = 0, m = -1 + extColsVec.size(); j <= m; j++) {
            ExtColumn &extCol = extColsVec.at(j);

            buf.draw(border.at(BorderStyle::SH), extCol.width);
            if (j < m) {
                buf.cursorPosition.y = usedHeight;
                buf.draw(border.at(BorderStyle::SV), maxCellHeight, true);

                if (i < n)
                    buf.draw(border.at(BorderStyle::SC));
                else
                    buf.draw(border.at(BorderStyle::SBV));
            }
        }

        //endregion

        usedHeight += 1;
    }
}


template<class TModel>
void DataTable<TModel>::prepareData(std::vector<TModel> &modifiedData) {
    if (!m_dataSource)
        return;

    pageNumber = std::clamp(pageNumber, size_t(0), m_pageCount);

    modifiedData.insert(modifiedData.cend(), m_dataSource->begin(), m_dataSource->end());

    if (filterBy.has_value()) {
        std::remove_if(
            modifiedData.begin(),
            modifiedData.end(),
            [&](const TModel &data) {
                auto &model = static_cast<const IModel &>(data);
                for (const DataTableColumnPair<TModel> &colPair : m_columns) {
                    std::string fieldValue = "";
                    if (model.tryGetFieldValue(colPair.first, fieldValue))
                        if (fieldValue.find(filterBy.value()) != std::string::npos)
                            return false;
                }
                return true;
            });
    }

    if (sortBy.has_value()) {
        DataTableColumn<TModel> column;
        auto sortBy = this->sortBy.value();
        if (this->tryGetColumn(sortBy, column)
            && column.visible) {
            if (column.sortPredicate != nullptr) {
                std::sort(modifiedData.begin(), modifiedData.end(), column.sortPredicate);
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

    if (!pageItemCount.has_value()) {
        m_pageCount = 1;
        pageNumber = 0;
    } else {
        auto items = pageItemCount.value();
        m_pageCount = modifiedData.size() / items + 1;
        pageNumber = std::clamp(pageNumber, size_t(0), m_pageCount - 1);

        auto begin = pageNumber * items;
        auto end = std::min(begin + items, modifiedData.size());
        modifiedData = std::vector<TModel>(modifiedData.begin() + begin, modifiedData.begin() + end);
    }
}


}



