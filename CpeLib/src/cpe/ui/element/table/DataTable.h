#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "cpe/ui/BaseWriter.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/IModel.h"
#include "cpe/ui/BaseWriterData.h"
#include "DataTableColumn.h"
#include "DataTableModel.h"

namespace cpe {

using DataTableColumnPair = std::pair<uint32_t, DataTableColumn *>;
using DataTableColumnVector = std::vector<DataTableColumnPair>;

template<class TData>
class DataTableData : public BaseWriterData {
public:
    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    DataTableColumn &getColumn(uint32_t fieldId);

    void setColumnList(DataTableColumnVector &list);

    void setDataSource(std::vector<TData> ds);

    const std::vector<TData> &getDataSource() const;

protected:
    StyledBorder mBorder;
    DataTableColumnVector *mColumns = nullptr;
    std::vector<TData> mDataSource;
};

template<class TData>
class DataTable : public BaseWriter<DataTableData<TData>> {
public:
    ~DataTable() override { }

    void addColumn(uint32_t fieldId, DataTableColumn &column);

protected:
    DataTableColumnVector mColumns;

    void onRun() override;

    void onWrite(Buffer &buf) override;
};


//region [ DataTableData ]

template<class TData>
const StyledBorder &DataTableData<TData>::getBorder() const {
    return mBorder;
}

template<class TData>
StyledBorder &DataTableData<TData>::getBorder() {
    return mBorder;
}

template<class TData>
DataTableColumn &DataTableData<TData>::getColumn(uint32_t fieldId) {
    return *(mColumns->at(fieldId).second);
}

template<class TData>
void DataTableData<TData>::setColumnList(DataTableColumnVector &list) {
    mColumns = &list;
}

template<class TData>
void DataTableData<TData>::setDataSource(std::vector<TData> ds) {
    mDataSource = ds;
}

template<class TData>
const std::vector<TData> &DataTableData<TData>::getDataSource() const {
    return mDataSource;
}

//endregion

template<class TData>
void DataTable<TData>::addColumn(uint32_t fieldId, DataTableColumn &column) {
    mColumns.push_back(DataTableColumnPair(fieldId, &column));
}

template<class TData>
void DataTable<TData>::onRun() {
    static_cast<DataTableData<TData>&>(this->getData()).setColumnList(mColumns);
}

template<class TData>
void DataTable<TData>::onWrite(Buffer &buf) {
    struct ExtColumn {
        uint32_t id;
        DataTableColumn *column;
        int width;
    };
    std::vector<ExtColumn> extColsVec;
    DataTableData<TData>& dtData = this->getData();

    const int offset = 1;
    int curColDrawPos = offset;
    int maxCellHeight = 0;

    //region [ HEADER ]
    auto srcColsCount = static_cast<int>(mColumns.size());
    int colDrawWidth = buf.getSize().getX() - srcColsCount;

    for (auto &colPair : mColumns) {
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
        colHeaderBuf.draw(extCol.column->getHeader());

        curColDrawPos += extCol.width + 1;
        maxCellHeight = std::max(maxCellHeight, colHeaderBuf.getUsedSize().getY());
    }

    //endregion

    //region [ HEADER UNDERLINE ]
    buf.getCursorPos() = Point(offset, maxCellHeight);

    for (size_t i = 0, n = -1 + extColsVec.size(); i <= n; i++) {
        const StyledBorder& bord = dtData.getBorder();
        ExtColumn& extCol = extColsVec.at(i);

        buf.draw(bord.at(BorderStyle::ST), extCol.width);
        if (i < n)
            buf.draw(bord.at(BorderStyle::STV));
    }

    maxCellHeight += 1;

    //endregion

    int usedHeight = 0;
    for (size_t i = 0, n = -1 + dtData.getDataSource().size(); i <= n; i++) {
        auto &srcDataItem = static_cast<const IModel&>(dtData.getDataSource().at(i));

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
            if (srcDataItem.getFieldValue(extColPair.id, modelDataField)) {
                modelDataStr
                    .setColor(extColPair.column->getCellTextColor())
                    .append(modelDataField);
            }
            cellBuf.draw(modelDataStr);

            curColDrawPos += extColPair.width + 1;
            maxCellHeight = std::max(maxCellHeight, cellBuf.getUsedSize().getY());
        }

        //endregion

        //region [ GRID ]

        buf.getCursorPos() = Point(offset, usedHeight + maxCellHeight);
        for (size_t j = 0, m = -1 + extColsVec.size(); j <= m; j++) {
            const StyledBorder& bord = dtData.getBorder();
            ExtColumn& extCol = extColsVec.at(j);

            buf.draw(bord.at(BorderStyle::SH), extCol.width);
            if (j < m) {
                buf.getCursorPos().getY() = usedHeight;
                buf.draw(bord.at(BorderStyle::SV), maxCellHeight, true);

                if (i < n)
                    buf.draw(bord.at(BorderStyle::SC));
                else
                    buf.draw(bord.at(BorderStyle::SBV));
            }
        }

        //endregion

        usedHeight += 1;
    }
}


}



