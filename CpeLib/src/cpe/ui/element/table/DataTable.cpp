#include "DataTable.h"

#include <cmath>

namespace cpe {

//region [ DataTableData ]

const StyledBorder &DataTableData::getBorder() const {
    return mBorder;
}

StyledBorder &DataTableData::getBorder() {
    return mBorder;
}

DataTableColumn &DataTableData::getColumn(uint32_t fieldId) {
    return *(mColumns->at(fieldId).second);
}

const DataSourceVector &DataTableData::getDataSource() const {
    return mDataSource;
}

void DataTableData::setColumnList(DataTableColumnVector &list) {
    mColumns = &list;
}

//endregion

void DataTable::addColumn(uint32_t fieldId, DataTableColumn &column) {
    mColumns.push_back(DataTableColumnPair(fieldId, &column));
}

void DataTable::onRun() {
    getData().setColumnList(mColumns);
}

void DataTable::onWrite(Buffer &buf) {
    struct ExtColumn {
        uint32_t id;
        DataTableColumn *column;
        int width;
    };
    std::vector<ExtColumn> extColsVec;

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
        buf.draw(getData().getBorder().at(BorderStyle::ST), extColsVec[i].width);
        if (i < n)
            buf.draw(getData().getBorder().at(BorderStyle::STV));
    }

    maxCellHeight += 1;

    //endregion

    int usedHeight = 0;
    for (size_t i = 0, n = -1 + getData().getDataSource().size(); i <= n; i++) {
        auto srcDataItem = getData().getDataSource()[i];

        usedHeight += maxCellHeight;
        maxCellHeight = 0;

        //region [ CELL ]

        curColDrawPos = offset;

        for (auto &extColPair : extColsVec) {
            if (!extColPair.column->getVisible())
                continue;

            auto cellBuf = buf.extract(
                Point(curColDrawPos, usedHeight),
                Point(extColPair.width, buf.getSize().getY() - usedHeight));

            StyledText modelDataStr;
            std::string modelDataField;
            if (srcDataItem->getFieldValue(extColPair.id, modelDataField)) {
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
            buf.draw(getData().getBorder().at(BorderStyle::SH), extColsVec[j].width);
            if (j < m) {
                buf.getCursorPos().getY() = usedHeight;
                buf.draw(getData().getBorder().at(BorderStyle::SV), maxCellHeight, true);

                if (i < n)
                    buf.draw(getData().getBorder().at(BorderStyle::SC));
                else
                    buf.draw(getData().getBorder().at(BorderStyle::SBV));
            }
        }

        //endregion

        usedHeight += 1;
    }
}


}





