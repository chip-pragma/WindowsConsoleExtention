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
    return *(mColumns->at(fieldId));
}

const DataSourceVector &DataTableData::getDataSource() const {
    return mDataSource;
}

void DataTableData::setColumnList(DataTableColumnMap &list) {
    mColumns = &list;
}

//endregion

void DataTable::addColumn(uint32_t fieldId, DataTableColumn &column) {
    mColumns.emplace(fieldId, &column);
}

void DataTable::onRun() {
    getData().setColumnList(mColumns);
}

void DataTable::onWrite(Buffer &buf) {
    // TODO доработать рисование таблицы

    auto colCount = mColumns.size();
    double colWidth = buf.getSize().getX() - (colCount - 1);

    struct Column {
        uint32_t id;
        DataTableColumn *column;
        int width;
    };
    std::vector<Column> cols;

    for (auto &pair : mColumns) {
        Column col{
            col.id = pair.first,
            col.column = pair.second
        };

        double w = (colWidth / colCount--);
        colWidth -= w;
        col.width = static_cast<int>(std::round(w));
        cols.push_back(col);

        auto header = buf.extract(buf.getCursorPos(), Point(col.width, ))
        header.draw(col.column->getHeader());
    }

    for (auto data : getData().getDataSource()) {
        for (auto &pair : cols) {
            if (!pair.second->getVisible())
                continue;

            StyledText modelData;
            modelData
                .append(pair.second->getHeader())
                .append(" : ")
                .setColor(pair.second->getCellTextColor());
            std::string modelDataField;
            if (data->getFieldValue(pair.first, modelDataField)) {
                modelData.append(modelDataField);
            }
            modelData
                .resetColor()
                .append("\n");
            buf.draw(modelData);
        }
    }
}


}





