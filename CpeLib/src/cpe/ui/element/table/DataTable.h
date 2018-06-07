#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "cpe/ui/BaseWriter.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/IModel.h"
#include "cpe/ui/BaseWriterData.h"
#include "DataTableColumn.h"

namespace cpe {

using DataTableColumnPair = std::pair<uint32_t, DataTableColumn*>;
using DataTableColumnVector = std::vector<DataTableColumnPair>;
using DataSourceVector = std::vector<const IModel*>;

class DataTableData : public BaseWriterData {
public:
    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    DataTableColumn& getColumn(uint32_t fieldId);

    template<class TModel>
    void setDataSource(const std::vector<TModel*>& ds);

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

    void addColumn(uint32_t fieldId, DataTableColumn &column);

protected:
    DataTableColumnVector mColumns;

    void onRun() override;

    void onWrite(Buffer &buf) override;
};

template<class TModel>
void DataTableData::setDataSource(const std::vector<TModel*>& ds) {
    mDataSource.clear();
    for (auto model : ds) {
        mDataSource.push_back(static_cast<const IModel *>(model));
    }
}

}



