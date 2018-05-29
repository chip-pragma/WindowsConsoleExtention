#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "cpe/ui/BaseWriter.h"
#include "DataTableColumn.cpp"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/IModel.h"

namespace cpe {

using DataTableColumnVector = std::unordered_map<uint32_t, DataTableColumn*>;

class DataTableData {
public:
    enum CellBorder {
        DTCB_NONE = 0,
        DTCB_IN = 1,
        DTCB_OUT = 2,
        DTCB_V = 4,
        DTCB_H = 8,
        DTCB_BOX = DTCB_OUT | DTCB_V | DTCB_H,
        DTCB_GRID = DTCB_IN | DTCB_V | DTCB_H,
        DTCB_ALL = DTCB_IN | DTCB_OUT | DTCB_V | DTCB_H
    };

    CellBorder getCellBorder() const;

    CellBorder getCellBorder();

    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    DataTableColumn& getColumn(uint32_t fieldId);

    template<class TModel>
    void setDataSource(const std::vector<TModel> &ds);

    void setColumnList(DataTableColumnVector& list);

protected:
    std::vector<const IModel*> mDataSource;
    CellBorder mCellBorder;
    StyledBorder mBorder;
    DataTableColumnVector* mColumns = nullptr;
};

class DataTable : public BaseWriter<DataTableData> {
public:
    ~DataTable() override { }

    void addColumn(uint32_t fieldId, const DataTableColumn &column);

protected:
    DataTableColumnVector mColumns;

    void onBeforeRun() override;

    void onWrite(Buffer &buf) override;
};

}



