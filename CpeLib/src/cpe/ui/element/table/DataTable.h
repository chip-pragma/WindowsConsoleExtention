#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "cpe/ui/BaseWriter.h"
#include "DataTableColumn.cpp"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/IModel.h"
#include "cpe/ui/BaseWriterData.h"

namespace cpe {

using DataTableColumnVector = std::unordered_map<uint32_t, DataTableColumn*>;
using DataSourceVector = std::vector<const IModel*>;

class DataTableData : public BaseWriterData {
public:
    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    DataTableColumn& getColumn(uint32_t fieldId);

    template<class TModel>
    void setDataSource(const std::vector<TModel> &ds);

    const DataSourceVector& getDataSource() const;

    void setColumnList(DataTableColumnVector& list);

protected:
    DataSourceVector mDataSource;
    StyledBorder mBorder;
    DataTableColumnVector* mColumns = nullptr;
};

class DataTable : public BaseWriter<DataTableData> {
public:
    ~DataTable() override { }

    void addColumn(uint32_t fieldId, const DataTableColumn &column);

protected:
    DataTableColumnVector mColumns;

    void onRun() override;

    void onWrite(Buffer &buf) override;
};

}



