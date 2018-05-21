#include "DataTable.h"

namespace cpe {

//region [ DataTableData ]

DataTableData::CellBorder DataTableData::cell_border() const {
    return mCellBorder;
}

DataTableData::CellBorder DataTableData::cell_border() {
    return mCellBorder;
}

const StyledBorder &DataTableData::border() const {
    return mBorder;
}

StyledBorder &DataTableData::border() {
    return mBorder;
}

void DataTableData::add_column(uint32_t fieldId, const DataTableColumn &column) {
    mColumns.insert_or_assign(fieldId, column);
}

void DataTableData::remove_column(uint32_t fieldId) {
    mColumns.erase(fieldId);
}

template<class TModel>
void DataTableData::data_source(const std::vector<TModel> &ds) {
    for (const auto &model : ds) {
        mDataSource.push_back(static_cast<const IModel *>(model));
    }
}

//endregion


void DataTable::on_write(Buffer &buf) {
    // TODO Рисование таблицы
}



}





