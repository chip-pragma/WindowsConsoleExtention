#include "DataTable.h"

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

template<class TModel>
void DataTableData::setDataSource(const std::vector<TModel> &ds) {
    for (const auto &model : ds) {
        mDataSource.push_back(static_cast<const IModel *>(model));
    }
}

const DataSourceVector &DataTableData::getDataSource() const {
    return mDataSource;
}

void DataTableData::setColumnList(DataTableColumnVector &list) {
    mColumns = &list;
}

//endregion

void DataTable::addColumn(uint32_t fieldId, const DataTableColumn &column) {
    mColumns.emplace(fieldId, &column);
}

void DataTable::onRun() {
    getData().setColumnList(mColumns);
}

void DataTable::onWrite(Buffer &buf) {
    // TODO Рисование таблицы

    for (auto data : getData().getDataSource()) {
        for (auto& pair : mColumns) {
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





