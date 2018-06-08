#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <optional>

#include "cpe/ui/BaseWriter.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/IModel.h"
#include "cpe/ui/BaseWriterData.h"
#include "DataTableColumn.h"
#include "DataTableModel.h"

namespace cpe {

template<class TDataModel>
class DataTableData : public BaseWriterData {
public:
    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    bool tryGetColumn(uint32_t fieldId, DataTableColumn<TDataModel> &outColumn) const;

    void setColumnList(DataTableColumnVector<TDataModel> &list);

    const DataTableModel<TDataModel> &getModel() const;

    DataTableModel<TDataModel> &getModel();

protected:
    StyledBorder mBorder;
    DataTableColumnVector<TDataModel> *mColumns = nullptr;
    DataTableModel<TDataModel> mModel;
};

template<class TDataModel>
class DataTable : public BaseWriter<DataTableData<TDataModel>> {
public:
    ~DataTable() override { }

    void addColumn(uint32_t fieldId, DataTableColumn<TDataModel> &column);

protected:
    DataTableColumnVector<TDataModel> mColumns;

    void onRun() override;

    void onWrite(Buffer &buf) override;
};


//region [ DataTableData ]

template<class TDataModel>
const StyledBorder &DataTableData<TDataModel>::getBorder() const {
    return mBorder;
}

template<class TDataModel>
StyledBorder &DataTableData<TDataModel>::getBorder() {
    return mBorder;
}

template<class TDataModel>
bool DataTableData<TDataModel>::tryGetColumn(uint32_t fieldId, DataTableColumn<TDataModel> &outColumn) const {
    auto iter = std::find_if(mColumns->begin(),
                             mColumns->end(),
                             [&](const DataTableColumnPair<TDataModel> &pair) {
                                 bool equal = (pair.first == fieldId);
                                 if (equal)
                                     outColumn = *(pair.second);
                                 return equal;
                             }
    );
    return (iter != mColumns->end());
}

template<class TDataModel>
void DataTableData<TDataModel>::setColumnList(DataTableColumnVector<TDataModel> &list) {
    mColumns = &list;
}

template<class TDataModel>
const DataTableModel<TDataModel> &DataTableData<TDataModel>::getModel() const {
    return mModel;
}

template<class TDataModel>
DataTableModel<TDataModel> &DataTableData<TDataModel>::getModel() {
    return mModel;
}

//endregion

template<class TDataModel>
void DataTable<TDataModel>::addColumn(uint32_t fieldId, DataTableColumn<TDataModel> &column) {
    mColumns.push_back(DataTableColumnPair<TDataModel>(fieldId, &column));
}

template<class TDataModel>
void DataTable<TDataModel>::onRun() {
    static_cast<DataTableData<TDataModel> &>(this->getData()).setColumnList(mColumns);
}

template<class TDataModel>
void DataTable<TDataModel>::onWrite(Buffer &buf) {
    struct ExtColumn {
        uint32_t id;
        DataTableColumn<TDataModel> *column;
        int width;
    };
    std::vector<ExtColumn> extColsVec;
    DataTableData<TDataModel> &dtData = this->getData();

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
        const StyledBorder &bord = dtData.getBorder();
        ExtColumn &extCol = extColsVec.at(i);

        buf.draw(bord.at(BorderStyle::ST), extCol.width);
        if (i < n)
            buf.draw(bord.at(BorderStyle::STV));
    }

    maxCellHeight += 1;

    //endregion

    std::vector<TDataModel> dataModelList
        = static_cast<DataTableModel<TDataModel>&>(dtData.getModel())
            .apply(mColumns);
    int usedHeight = 0;
    for (size_t i = 0, n = -1 + dataModelList.size(); i <= n; i++) {
        auto &srcDataItem = static_cast<const IModel &>(dataModelList.at(i));

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
            const StyledBorder &bord = dtData.getBorder();
            ExtColumn &extCol = extColsVec.at(j);

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



