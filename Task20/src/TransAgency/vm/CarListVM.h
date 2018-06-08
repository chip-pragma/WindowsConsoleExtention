#pragma once

#include <vector>

#include <cpe/ui/BaseViewModel.h>
#include <cpe/ui/element/table/DataTable.h>
#include <cpe/ui/element/Label.h>
#include <cpe/ui/element/table/DataTableModel.h>

#include "TransAgency/model/Car.h"
#include "TransAgency/common.h"

class CarListVM : public cpe::BaseViewModel {
public:
    ~CarListVM() override;

    void onDataTableInit(cpe::DataTableData<Car>& data);

    void onLabelPageInit(cpe::LabelData& data);

private:
    cpe::DataTableModel<Car> *mTableModel;
};


