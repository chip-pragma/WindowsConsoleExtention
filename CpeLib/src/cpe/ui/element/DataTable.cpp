#include "DataTable.h"

namespace cpe {

//region [ DataTableData ]

DataTableData::CellBorder DataTableData::getCellBorder() const {
    return mCellBorder;
}

DataTableData::CellBorder DataTableData::getCellBorder() {
    return mCellBorder;
}

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

void DataTableData::setColumnList(DataTableColumnVector &list) {
    mColumns = &list;
}

//endregion

void DataTable::addColumn(uint32_t fieldId, const DataTableColumn &column) {
    mColumns.emplace(fieldId, &column);
}

void DataTable::onBeforeRun() {
    getData().setColumnList(mColumns);
}

void DataTable::onWrite(Buffer &buf) {

    // TODO Рисование таблицы
}


}





