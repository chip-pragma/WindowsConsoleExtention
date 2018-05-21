#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "BaseWriter.h"
#include "DataTableColumn.cpp"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/IModel.h"

namespace cpe {

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

    CellBorder cell_border() const;

    CellBorder cell_border();

    const StyledBorder &border() const;

    StyledBorder &border();

    void add_column(uint32_t fieldId, const DataTableColumn &column);

    void remove_column(uint32_t fieldId);

    template<class TModel>
    void data_source(const std::vector<TModel> &ds);

protected:
    std::unordered_map<uint32_t, DataTableColumn> mColumns;
    std::vector<const IModel*> mDataSource;
    CellBorder mCellBorder;
    StyledBorder mBorder;
};

class DataTable : public BaseWriter<DataTableData> {
public:
    ~DataTable() override { }

protected:

    void on_write(Buffer &buf) override;
};

}



